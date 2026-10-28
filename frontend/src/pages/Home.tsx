import { useState } from "react";
import { Link } from "react-router-dom";
import "../styles/home.css";

function Home() {
    return (
        <main className="home">
            <section className="cipher-links">
                <div className="caesar-link">
                    <Link to="/Caesar">Caesar Cipher</Link>
                </div>

                <div className="monoalphabetic-link">
                    <Link to="/Monoalphabetic">Monoalphabetic Cipher</Link>
                </div>

                <div className="vignere-link">
                    <Link to="/Vigenere">Vigenere Cipher</Link>
                </div>
            </section>
        </main>
    );
}

export default Home;