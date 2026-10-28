import { Link } from "react-router-dom";
import "../styles/Header.css";

function Header() {
    return (
        <header className="site-header">
            <Link to="/" className="logo-link">
                <img src="/logo.png" alt="Home" className="site-logo"/>
            </Link>

            <h1 className="site-title">CRYPTO LAB</h1>
        </header>
    );
}

export default Header;