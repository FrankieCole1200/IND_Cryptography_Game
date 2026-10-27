import { useState } from "react";
import "./App.css";

// Stage of the game.
// setup = User enters messages m0 and m1
// challenge = User tries to guess which message has been encrypted
// result = User finds out if their guess was correct
type Stage = "setup" | "challenge" | "result";

// A 'challenge' consists of some ciphertext to be decoded by the adversary
// and a roundID, to keep track of how many round have been played
type Challenge = {
    ciphertext: string;
    roundId: string;
};

// Demo-only encryption. This will be replaced by the C++ backend.
// Copy of the function where the challeneger randomly chooses a message to encrypt and returns it's ciphertext.
// INPUT: messages m0 and m1
// OUTPUT: a Challenge object (defined above), and the hidden bit (randomly chosen)
function demoChallenge(m0: string, m1: string): {
    challenge: Challenge;
    hiddenBit: 0 | 1;
} {
    const hiddenBit = Math.floor(Math.random() * 2) as 0 | 1;
    const message = hiddenBit === 0 ? m0 : m1; // message = m0 if hiddenBit == 0 and m1 if hiddenBit == 1
    const shift = Math.floor(Math.random() * 95); // choose a random caesar shift

    // encrypt the message
    // Array.from() converts the string "message" into an array of characters 
    // and applies the callback (2nd param) to each character.
    // The callback just shifts each characters unicode by the shift amount and keeps that character
    const ciphertext = Array.from(message, (character) => {
        const code = character.charCodeAt(0);
        return String.fromCharCode(32 + ((code - 32 + shift) % 95));
    }).join("");

    return {
        challenge: {ciphertext, roundId: crypto.randomUUID(),},
        hiddenBit,
    };
}

function App() {
    const [m0, setM0] = useState("HELLO");
    const [m1, setM1] = useState("WORLD");
    const [stage, setStage] = useState<Stage>("setup");
    const [challenge, setChallenge] = useState<Challenge | null>(null);
    const [demoHiddenBit, setDemoHiddenBit] = useState<0 | 1 | null>(null);
    const [guess, setGuess] = useState<0 | 1 | null>(null);
    const [correct, setCorrect] = useState<boolean | null>(null);
    const [wins, setWins] = useState(0);
    const [rounds, setRounds] = useState(0);

    // Before allowing the user to generate a challenge, we check the inputs:
    // Each message must have some characters and the same amount.
    // In addition, each character must be from the message space which we defined as 
    // characters with ascii in the range 32-126
    const validMessages = (m0.length > 0) && (m0.length === m1.length) &&
        [...m0, ...m1].every( // ...m0/m1 uses the 'spread' operator to create an array containing the characters from both messages.
            (character) => (character.charCodeAt(0) >= 32) && (character.charCodeAt(0) <= 126)
        );

    // When "Generate Challenge" button pressed, this is executed
    function startGame() {
        if (!validMessages) return;

        const result = demoChallenge(m0, m1); // result is a Challenge object and bit representing the encrypted message  
        setChallenge(result.challenge);
        setDemoHiddenBit(result.hiddenBit);
        setGuess(null);
        setCorrect(null);
        setStage("challenge"); // move to next stage
    }

    // Checks if the user correctly guessed which message was encrypted
    function submitGuess() {
        if (guess === null || demoHiddenBit === null) return; // edge case incase user has not chosen a message or challeneger has chosen a message to encrypt

        const won = guess === demoHiddenBit;
        setCorrect(won);
        setRounds((previous) => previous + 1); // increment round number

        if (won) {
            setWins((previous) => previous + 1); // increment win number
        }

        setStage("result"); // move to next stage
    }

    // Function to reset the game back to first stage.
    function resetGame() {
        setChallenge(null);
        setDemoHiddenBit(null);
        setGuess(null);
        setCorrect(null);
        setStage("setup");
    }

    return (
        <main className="app">
            <header className="page-header">
                <p className="eyebrow">CRYPTOGRAPHY LAB</p>
                <h1>IND-EAV Game</h1>
                <p className="subtitle">
                    Can you distinguish which plaintext was encrypted?
                </p>
                <span className="demo-label">
                    Frontend demo — not a secure cryptographic experiment
                </span>
            </header>

            {/* This "section" contains all the code for the GAME-CARD */}
            <section className="game-card">

                {/* card heading text is determined by game stage. */}
                <div className="card-heading">
                    <h2>
                        {stage === "setup" && "Choose your messages"}
                        {stage === "challenge" && "Challenge ciphertext"}
                        {stage === "result" && "Round result"}
                    </h2>
                    {/* Indicates what stage we are in, setup = 1, challenge = 2, else/result = 3 */}
                    <span className="stage-label">
                        {stage === "setup" ? "01 / 03" : stage === "challenge" ? "02 / 03" : "03 / 03"}
                    </span>
                </div>

                {/* Contents of the game-card can be in 3 states depending on the stage of the game */}

                {/* Stage 1: setup */}
                {stage === "setup" && (
                    <>
                        <p className="helper">
                            Enter two messages of equal length. The challenger will
                            randomly encrypt one of them.
                        </p>

                        {/* The message grid contains 2 text boxes. */}
                        <div className="message-grid">
                            <label>
                                Message m₀
                                <textarea
                                    value={m0} // by default display the current value of the variable m0
                                    onChange={(event) => setM0(event.target.value)}
                                    rows={3} // How many rows are displayed. Effects visual length of text box
                                    maxLength={200} // 200 character limit
                                />
                            </label>

                            <label>
                                Message m₁
                                <textarea
                                    value={m1}
                                    onChange={(event) => setM1(event.target.value)}
                                    rows={3}
                                    maxLength={200}
                                />
                            </label>
                        </div>

                        {/* If validMessages is false, then the text will be made visible. */}
                        {!validMessages && (
                            <p className="error">
                                Both messages must be nonempty, have equal lengths,
                                and contain only printable ASCII characters.
                            </p>
                        )}

                        {/* When clicked, startGame is executed, but if the messages are invalid, 
                        the button will be disabled */}
                        <button className="primary-button" onClick={startGame} disabled={!validMessages}>
                            Generate challenge
                        </button>
                    </>
                )}

                {/* Stage 2: challenge */}
                {stage === "challenge" && challenge && (
                    <>
                        <p className="helper">
                            The challenger has selected one of your messages.
                            Examine the ciphertext and make your guess.
                        </p>

                        {/* This is a box that displays the ciphertext of the encrypted message */}
                        <div className="ciphertext-box">
                            <span>CHALLENGE CIPHERTEXT</span>
                            <code>{challenge.ciphertext}</code>
                        </div>

                        {/* Here we create 2 buttons that allow the user to pick one of the messages
                        they think was enccrypted.
                        If they pick a button then its class name = option selected, else = option 
                        When a button is clicked, setGuess is executed which updates their guess bit*/}
                        <div className="guess-options">
                            {/* Display message m0 */}
                            <button className={guess === 0 ? "option selected" : "option"} onClick={() => setGuess(0)}>
                                <span>Message m₀</span>
                                <strong>{m0}</strong>
                            </button>

                            {/* Display message m1 */}
                            <button className={guess === 1 ? "option selected" : "option"} onClick={() => setGuess(1)}>
                                <span>Message m₁</span>
                                <strong>{m1}</strong>
                            </button>
                        </div>
                        
                        {/* Button for submitting guess. Executes submitGuess when pressed, unless the user hasn't
                        picked a message yet */}
                        <button className="primary-button" disabled={guess === null} onClick={submitGuess}>
                            Submit guess
                        </button>
                    </>
                )}

                {/* Stage 3: result */}
                {/* This part of the code uses the 'correct' variable to decide what to display */}
                {stage === "result" && (
                    <div className="result">
                        {/* Displays a tick or cross*/}
                        <div className={correct ? "result-icon win" : "result-icon lose"}>
                            {correct ? "✓" : "✕"}
                        </div>

                        <h3>{correct ? "Correct guess!" : "Incorrect guess"}</h3>
                        
                        <p> The challenger encrypted message{" "} <strong>m{demoHiddenBit}</strong>. </p>
                        
                        <p> You guessed <strong>m{guess}</strong>. </p>
                        
                        {/* This button when pressed restarts the game back to stage "setup" */}
                        <button className="primary-button" onClick={resetGame}>
                            Play another round
                        </button>
                    </div>
                )}
            </section>
            
            {/* This "section" contains all the code for the stats boxes */}
            <section className="stats">
                <div> {/* box 1 */}
                    <span>Rounds played</span>
                    <strong>{rounds}</strong>
                </div>

                <div> {/* box 2 */}
                    <span>Correct guesses</span>
                    <strong>{wins}</strong>
                </div>

                <div> {/* box 3 */}
                    <span>Success rate</span>
                    <strong>
                        {rounds === 0 ? "_" : `${((wins / rounds) * 100).toFixed(1)}%`}
                    </strong>
                </div>
                
            </section>
            
            {/* Text for bottom of screen */}
            <footer>
                In an IND-EAV experiment, the adversary receives only the
                challenge ciphertext, not the secret key or hidden bit.
            </footer>
        </main>
    );
}

export default App;
