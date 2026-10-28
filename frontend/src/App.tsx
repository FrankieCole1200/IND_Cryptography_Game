import { StrictMode } from "react";
import { createRoot } from "react-dom/client";
import { BrowserRouter, Routes, Route } from "react-router-dom";

import "./styles/index.css";

import Header from "./components/Header";
import Home from "./pages/Home";
import Caesar from "./pages/Caesar";
import Monoalphabetic from "./pages/Monoalphabetic";
import Vigenere from "./pages/Vigenere";

createRoot(document.getElementById("root")!).render(
  <StrictMode>
    <BrowserRouter>
      <Header />

      <Routes>
        <Route path="/" element={<Home />} />
        <Route path="/caesar" element={<Caesar />} />
        <Route path="/monoalphabetic" element={<Monoalphabetic />} />
        <Route path="/vigenere" element={<Vigenere />} />
      </Routes>
    </BrowserRouter>
  </StrictMode>
);