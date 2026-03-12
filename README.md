<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Matrix Addition System — Case Study 167</title>
<link href="https://fonts.googleapis.com/css2?family=Space+Mono:ital,wght@0,400;0,700;1,400&family=Syne:wght@400;600;700;800&display=swap" rel="stylesheet">
<style>
  :root {
    --bg: #050a0f;
    --surface: #0b1420;
    --surface2: #0f1e30;
    --accent: #00e5ff;
    --accent2: #7b2fff;
    --accent3: #00ff9d;
    --text: #c8dff0;
    --muted: #4a6a85;
    --border: rgba(0,229,255,0.15);
    --glow: 0 0 30px rgba(0,229,255,0.2);
  }

  *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Syne', sans-serif;
    min-height: 100vh;
    overflow-x: hidden;
  }

  /* Grid background */
  body::before {
    content: '';
    position: fixed;
    inset: 0;
    background-image:
      linear-gradient(rgba(0,229,255,0.03) 1px, transparent 1px),
      linear-gradient(90deg, rgba(0,229,255,0.03) 1px, transparent 1px);
    background-size: 40px 40px;
    pointer-events: none;
    z-index: 0;
  }

  /* Ambient glow blobs */
  body::after {
    content: '';
    position: fixed;
    width: 600px; height: 600px;
    background: radial-gradient(circle, rgba(123,47,255,0.08) 0%, transparent 70%);
    top: -100px; right: -100px;
    pointer-events: none;
    z-index: 0;
  }

  .container {
    max-width: 900px;
    margin: 0 auto;
    padding: 60px 24px;
    position: relative;
    z-index: 1;
  }

  /* ─── HERO ─── */
  .hero {
    text-align: center;
    padding: 60px 0 50px;
    position: relative;
  }

  .hero-tag {
    display: inline-block;
    font-family: 'Space Mono', monospace;
    font-size: 11px;
    letter-spacing: 3px;
    color: var(--accent);
    background: rgba(0,229,255,0.07);
    border: 1px solid var(--border);
    padding: 6px 16px;
    border-radius: 2px;
    margin-bottom: 28px;
    text-transform: uppercase;
    animation: fadeDown 0.6s ease both;
  }

  .hero h1 {
    font-family: 'Syne', sans-serif;
    font-size: clamp(36px, 7vw, 72px);
    font-weight: 800;
    line-height: 1.05;
    letter-spacing: -2px;
    margin-bottom: 6px;
    animation: fadeDown 0.6s 0.1s ease both;
  }

  .hero h1 span.matrix { color: var(--accent); }
  .hero h1 span.plus {
    color: var(--accent2);
    display: inline-block;
    animation: pulse 2s infinite;
  }

  .hero-sub {
    font-family: 'Space Mono', monospace;
    font-size: 13px;
    color: var(--muted);
    margin: 18px 0 0;
    animation: fadeDown 0.6s 0.2s ease both;
  }

  .author-badge {
    display: inline-flex;
    align-items: center;
    gap: 10px;
    margin-top: 32px;
    background: var(--surface);
    border: 1px solid var(--border);
    padding: 10px 20px;
    border-radius: 100px;
    font-size: 13px;
    font-weight: 600;
    animation: fadeDown 0.6s 0.3s ease both;
  }

  .author-badge .dot {
    width: 8px; height: 8px;
    background: var(--accent3);
    border-radius: 50%;
    box-shadow: 0 0 8px var(--accent3);
    animation: blink 1.5s infinite;
  }

  /* ─── EXAMPLE MATRICES ─── */
  .matrix-showcase {
    display: grid;
    grid-template-columns: 1fr auto 1fr auto 1fr;
    align-items: center;
    gap: 16px;
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 12px;
    padding: 32px;
    margin: 48px 0;
    box-shadow: var(--glow);
    animation: fadeUp 0.7s 0.4s ease both;
  }

  .matrix-block { text-align: center; }

  .matrix-label {
    font-family: 'Space Mono', monospace;
    font-size: 11px;
    letter-spacing: 2px;
    color: var(--muted);
    text-transform: uppercase;
    margin-bottom: 14px;
  }

  .matrix-grid {
    display: inline-grid;
    gap: 2px;
    position: relative;
  }

  .matrix-grid::before, .matrix-grid::after {
    content: '';
    position: absolute;
    top: 0; bottom: 0;
    width: 3px;
    border: 2px solid;
    border-radius: 2px;
  }

  .matrix-grid::before { left: -10px; border-right: none; }
  .matrix-grid::after  { right: -10px; border-left: none; }

  .matrix-block:nth-child(1) .matrix-grid::before,
  .matrix-block:nth-child(1) .matrix-grid::after { border-color: var(--accent); }
  .matrix-block:nth-child(3) .matrix-grid::before,
  .matrix-block:nth-child(3) .matrix-grid::after { border-color: var(--accent2); }
  .matrix-block:nth-child(5) .matrix-grid::before,
  .matrix-block:nth-child(5) .matrix-grid::after { border-color: var(--accent3); }

  .matrix-row { display: flex; gap: 2px; }

  .matrix-cell {
    width: 44px; height: 44px;
    display: flex; align-items: center; justify-content: center;
    font-family: 'Space Mono', monospace;
    font-size: 16px;
    font-weight: 700;
    border-radius: 4px;
    transition: transform 0.2s;
  }

  .matrix-block:nth-child(1) .matrix-cell { background: rgba(0,229,255,0.07); color: var(--accent); }
  .matrix-block:nth-child(3) .matrix-cell { background: rgba(123,47,255,0.1); color: var(--accent2); }
  .matrix-block:nth-child(5) .matrix-cell { background: rgba(0,255,157,0.07); color: var(--accent3); }

  .matrix-cell:hover { transform: scale(1.1); }

  .op-symbol {
    font-size: 32px;
    font-weight: 800;
    color: var(--muted);
    text-align: center;
  }

  .op-symbol.eq { color: var(--text); }

  /* ─── SECTIONS ─── */
  .section {
    margin: 40px 0;
    animation: fadeUp 0.6s ease both;
  }

  .section-header {
    display: flex;
    align-items: center;
    gap: 12px;
    margin-bottom: 20px;
  }

  .section-icon {
    width: 36px; height: 36px;
    display: flex; align-items: center; justify-content: center;
    font-size: 16px;
    background: rgba(0,229,255,0.07);
    border: 1px solid var(--border);
    border-radius: 8px;
    flex-shrink: 0;
  }

  .section-title {
    font-size: 18px;
    font-weight: 700;
    letter-spacing: -0.3px;
  }

  .line-accent {
    flex: 1;
    height: 1px;
    background: linear-gradient(90deg, var(--border), transparent);
  }

  /* ─── CARDS ─── */
  .cards {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
    gap: 12px;
  }

  .card {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius: 10px;
    padding: 18px;
    transition: border-color 0.2s, transform 0.2s, box-shadow 0.2s;
  }

  .card:hover {
    border-color: rgba(0,229,255,0.4);
    transform: translateY(-2px);
    box-shadow: 0 8px 24px rgba(0,0,0,0.3);
  }

  .card-icon { font-size: 22px; margin-bottom: 10px; }
  .card-title { font-size: 13px; font-weight: 700; margin-bottom: 4px; }
  .card-desc { font-size: 12px; color: var(--muted); line-height: 1.5; }

  /* ─── STEPS ─── */
  .steps { display: flex; flex-direction: column; gap: 0; }

  .step {
    display: flex;
    gap: 20px;
    align-items: flex-start;
    position: relative;
  }

  .step:not(:last-child)::after {
    content: '';
    position: absolute;
    left: 18px; top: 44px; bottom: -8px;
    width: 1px;
    background: linear-gradient(to bottom, var(--border), transparent);
  }

  .step-num {
    width: 36px; height: 36px;
    border-radius: 50%;
    background: var(--surface2);
    border: 1px solid var(--border);
    display: flex; align-items: center; justify-content: center;
    font-family: 'Space Mono', monospace;
    font-size: 12px;
    font-weight: 700;
    color: var(--accent);
    flex-shrink: 0;
    margin-top: 2px;
  }

  .step-content { padding-bottom: 24px; }
  .step-title { font-size: 14px; font-weight: 700; margin-bottom: 3px; }
  .step-desc { font-size: 13px; color: var(--muted); line-height: 1.5; }

  /* ─── CODE BLOCK ─── */
  .code-block {
    background: #020810;
    border: 1px solid var(--border);
    border-radius: 10px;
    overflow: hidden;
  }

  .code-header {
    display: flex;
    align-items: center;
    gap: 8px;
    padding: 12px 16px;
    background: var(--surface);
    border-bottom: 1px solid var(--border);
  }

  .code-dot { width: 10px; height: 10px; border-radius: 50%; }
  .code-dot:nth-child(1) { background: #ff5f57; }
  .code-dot:nth-child(2) { background: #febc2e; }
  .code-dot:nth-child(3) { background: #28c840; }
  .code-filename {
    margin-left: 8px;
    font-family: 'Space Mono', monospace;
    font-size: 12px;
    color: var(--muted);
  }

  .code-content {
    padding: 20px;
    font-family: 'Space Mono', monospace;
    font-size: 13px;
    line-height: 1.8;
    color: #7eb8d4;
    white-space: pre;
    overflow-x: auto;
  }

  .code-content .kw { color: var(--accent2); }
  .code-content .fn { color: var(--accent); }
  .code-content .str { color: var(--accent3); }
  .code-content .cm { color: #3a5a72; font-style: italic; }
  .code-content .num { color: #ff9d5c; }

  /* ─── TECH TAGS ─── */
  .tech-tags { display: flex; flex-wrap: wrap; gap: 10px; }

  .tech-tag {
    display: flex;
    align-items: center;
    gap: 8px;
    background: var(--surface);
    border: 1px solid var(--border);
    padding: 8px 16px;
    border-radius: 6px;
    font-family: 'Space Mono', monospace;
    font-size: 12px;
    font-weight: 700;
    transition: border-color 0.2s, box-shadow 0.2s;
  }

  .tech-tag:hover {
    border-color: var(--accent);
    box-shadow: 0 0 16px rgba(0,229,255,0.1);
  }

  .tech-tag .dot {
    width: 6px; height: 6px; border-radius: 50%;
    background: var(--accent);
    box-shadow: 0 0 6px var(--accent);
  }

  /* ─── FILE TREE ─── */
  .file-tree {
    background: #020810;
    border: 1px solid var(--border);
    border-radius: 10px;
    padding: 24px;
    font-family: 'Space Mono', monospace;
    font-size: 13px;
    line-height: 2;
  }

  .tree-root { color: var(--accent); font-weight: 700; }
  .tree-branch { color: var(--muted); }
  .tree-file { color: var(--text); }
  .tree-desc { color: var(--muted); font-size: 11px; }

  /* ─── FUTURE GRID ─── */
  .future-grid {
    display: grid;
    grid-template-columns: repeat(auto-fill, minmax(180px, 1fr));
    gap: 12px;
  }

  .future-item {
    background: var(--surface);
    border: 1px dashed var(--border);
    border-radius: 10px;
    padding: 18px;
    text-align: center;
    transition: border-color 0.2s, background 0.2s;
    cursor: default;
  }

  .future-item:hover {
    border-color: var(--accent2);
    background: rgba(123,47,255,0.05);
  }

  .future-item .fi { font-size: 28px; margin-bottom: 8px; }
  .future-item .ft { font-size: 13px; font-weight: 700; }
  .future-item .fd { font-size: 11px; color: var(--muted); margin-top: 4px; }

  /* ─── FOOTER ─── */
  .footer {
    text-align: center;
    padding: 48px 0 24px;
    border-top: 1px solid var(--border);
    margin-top: 60px;
  }

  .footer-name {
    font-size: 22px;
    font-weight: 800;
    letter-spacing: -0.5px;
    margin-bottom: 6px;
  }

  .footer-meta {
    font-family: 'Space Mono', monospace;
    font-size: 12px;
    color: var(--muted);
    line-height: 2;
  }

  .footer-accent {
    display: inline-block;
    width: 40px; height: 3px;
    background: linear-gradient(90deg, var(--accent), var(--accent2));
    border-radius: 2px;
    margin: 16px auto;
  }

  /* ─── DIVIDER ─── */
  .divider {
    height: 1px;
    background: linear-gradient(90deg, transparent, var(--border), transparent);
    margin: 48px 0;
  }

  /* ─── ANIMATIONS ─── */
  @keyframes fadeDown {
    from { opacity: 0; transform: translateY(-16px); }
    to   { opacity: 1; transform: translateY(0); }
  }

  @keyframes fadeUp {
    from { opacity: 0; transform: translateY(16px); }
    to   { opacity: 1; transform: translateY(0); }
  }

  @keyframes pulse {
    0%, 100% { opacity: 1; }
    50% { opacity: 0.5; }
  }

  @keyframes blink {
    0%, 100% { opacity: 1; }
    50% { opacity: 0.3; }
  }

  /* Stagger cards */
  .cards .card:nth-child(1) { animation-delay: 0.05s; }
  .cards .card:nth-child(2) { animation-delay: 0.10s; }
  .cards .card:nth-child(3) { animation-delay: 0.15s; }
  .cards .card:nth-child(4) { animation-delay: 0.20s; }
  .cards .card:nth-child(5) { animation-delay: 0.25s; }

  @media (max-width: 600px) {
    .matrix-showcase {
      grid-template-columns: 1fr;
      text-align: center;
    }
    .op-symbol { transform: rotate(90deg); }
  }
</style>
</head>
<body>
<div class="container">

  <!-- HERO -->
  <div class="hero">
    <div class="hero-tag">⬡ Case Study 167 &nbsp;·&nbsp; C++ Project</div>
    <h1>
      <span class="matrix">Matrix</span><br>
      Addition <span class="plus">+</span> System
    </h1>
    <p class="hero-sub">// 2D Arrays · Nested Loops · Input Validation · Menu-Driven Interface</p>
    <div class="author-badge">
      <span class="dot"></span>
      Sejal Singh &nbsp;·&nbsp; B.Tech CSE &nbsp;·&nbsp; 2025–2029
    </div>
  </div>

  <!-- MATRIX SHOWCASE -->
  <div class="matrix-showcase">
    <div class="matrix-block">
      <div class="matrix-label">Matrix A</div>
      <div class="matrix-grid">
        <div class="matrix-row">
          <div class="matrix-cell">1</div>
          <div class="matrix-cell">2</div>
        </div>
        <div class="matrix-row">
          <div class="matrix-cell">3</div>
          <div class="matrix-cell">4</div>
        </div>
      </div>
    </div>

    <div class="op-symbol">+</div>

    <div class="matrix-block">
      <div class="matrix-label">Matrix B</div>
      <div class="matrix-grid">
        <div class="matrix-row">
          <div class="matrix-cell">5</div>
          <div class="matrix-cell">6</div>
        </div>
        <div class="matrix-row">
          <div class="matrix-cell">7</div>
          <div class="matrix-cell">8</div>
        </div>
      </div>
    </div>

    <div class="op-symbol eq">=</div>

    <div class="matrix-block">
      <div class="matrix-label">Result A + B</div>
      <div class="matrix-grid">
        <div class="matrix-row">
          <div class="matrix-cell">6</div>
          <div class="matrix-cell">8</div>
        </div>
        <div class="matrix-row">
          <div class="matrix-cell">10</div>
          <div class="matrix-cell">12</div>
        </div>
      </div>
    </div>
  </div>

  <!-- OVERVIEW -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">📌</div>
      <div class="section-title">Project Overview</div>
      <div class="line-accent"></div>
    </div>
    <p style="font-size:15px; line-height:1.8; color:var(--text);">
      A console-based <strong style="color:var(--accent)">Matrix Addition System</strong> written in C++ that lets users input two same-dimension matrices and computes their element-wise sum. The program demonstrates core C++ concepts — 2D arrays, nested loops, functions, and robust input validation — presented through a clean, menu-driven interface.
    </p>
  </div>

  <!-- OBJECTIVES -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">🎯</div>
      <div class="section-title">Objectives</div>
      <div class="line-accent"></div>
    </div>
    <div class="cards">
      <div class="card">
        <div class="card-icon">📚</div>
        <div class="card-title">2D Array Mastery</div>
        <div class="card-desc">Understand matrix representation using two-dimensional arrays in C++</div>
      </div>
      <div class="card">
        <div class="card-icon">🔁</div>
        <div class="card-title">Nested Loops</div>
        <div class="card-desc">Perform element-wise addition using row × column iteration patterns</div>
      </div>
      <div class="card">
        <div class="card-icon">🧩</div>
        <div class="card-title">Modular Code</div>
        <div class="card-desc">Practice structured, function-based programming for clean architecture</div>
      </div>
      <div class="card">
        <div class="card-icon">🛡</div>
        <div class="card-title">Input Validation</div>
        <div class="card-desc">Learn safe input techniques to handle invalid user entries gracefully</div>
      </div>
      <div class="card">
        <div class="card-icon">📊</div>
        <div class="card-title">Formatted Output</div>
        <div class="card-desc">Display matrices in aligned, readable table layouts using iomanip</div>
      </div>
    </div>
  </div>

  <!-- FEATURES -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">✨</div>
      <div class="section-title">Features</div>
      <div class="line-accent"></div>
    </div>
    <div class="cards">
      <div class="card">
        <div class="card-icon">🧭</div>
        <div class="card-title">Menu Interface</div>
        <div class="card-desc">Intuitive menu-driven flow for easy program navigation</div>
      </div>
      <div class="card">
        <div class="card-icon">🔐</div>
        <div class="card-title">Safe Input</div>
        <div class="card-desc">Validates rows and columns to prevent crashes and bad data</div>
      </div>
      <div class="card">
        <div class="card-icon">📏</div>
        <div class="card-title">Up to 10×10</div>
        <div class="card-desc">Supports any square or rectangular matrix up to 10 × 10</div>
      </div>
      <div class="card">
        <div class="card-icon">📋</div>
        <div class="card-title">Table Display</div>
        <div class="card-desc">Matrices printed in clean, aligned table format for readability</div>
      </div>
    </div>
  </div>

  <!-- CODE SNIPPET -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">💻</div>
      <div class="section-title">Core Logic Snippet</div>
      <div class="line-accent"></div>
    </div>
    <div class="code-block">
      <div class="code-header">
        <div class="code-dot"></div>
        <div class="code-dot"></div>
        <div class="code-dot"></div>
        <div class="code-filename">matrix.cpp</div>
      </div>
      <div class="code-content"><span class="cm">// Matrix Addition — element-wise sum</span>
<span class="kw">void</span> <span class="fn">addMatrices</span>(<span class="kw">int</span> A[][<span class="num">10</span>], <span class="kw">int</span> B[][<span class="num">10</span>], <span class="kw">int</span> result[][<span class="num">10</span>],
                  <span class="kw">int</span> rows, <span class="kw">int</span> cols) {
    <span class="kw">for</span> (<span class="kw">int</span> i = <span class="num">0</span>; i &lt; rows; i++) {
        <span class="kw">for</span> (<span class="kw">int</span> j = <span class="num">0</span>; j &lt; cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

<span class="cm">// Display matrix in formatted table layout</span>
<span class="kw">void</span> <span class="fn">displayMatrix</span>(<span class="kw">int</span> M[][<span class="num">10</span>], <span class="kw">int</span> rows, <span class="kw">int</span> cols) {
    <span class="kw">for</span> (<span class="kw">int</span> i = <span class="num">0</span>; i &lt; rows; i++) {
        <span class="kw">for</span> (<span class="kw">int</span> j = <span class="num">0</span>; j &lt; cols; j++)
            cout &lt;&lt; setw(<span class="num">5</span>) &lt;&lt; M[i][j];
        cout &lt;&lt; <span class="str">"\n"</span>;
    }
}</div>
    </div>
  </div>

  <!-- HOW IT WORKS -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">⚙️</div>
      <div class="section-title">How It Works</div>
      <div class="line-accent"></div>
    </div>
    <div class="steps">
      <div class="step">
        <div class="step-num">01</div>
        <div class="step-content">
          <div class="step-title">Launch & Main Menu</div>
          <div class="step-desc">Program starts and presents the main menu with options to add matrices or exit</div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">02</div>
        <div class="step-content">
          <div class="step-title">Select Dimensions</div>
          <div class="step-desc">User inputs number of rows and columns with validation enforcing a max of 10×10</div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">03</div>
        <div class="step-content">
          <div class="step-title">Enter Matrix A</div>
          <div class="step-desc">User fills in all elements of the first matrix row by row</div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">04</div>
        <div class="step-content">
          <div class="step-title">Enter Matrix B</div>
          <div class="step-desc">User fills in all elements of the second matrix using the same dimensions</div>
        </div>
      </div>
      <div class="step">
        <div class="step-num">05</div>
        <div class="step-content">
          <div class="step-title">Compute & Display</div>
          <div class="step-desc">Program adds the matrices element-by-element and displays A, B, and the Result in formatted table layout</div>
        </div>
      </div>
    </div>
  </div>

  <!-- TECHNOLOGIES -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">🛠</div>
      <div class="section-title">Technologies Used</div>
      <div class="line-accent"></div>
    </div>
    <div class="tech-tags">
      <div class="tech-tag"><span class="dot"></span> C++</div>
      <div class="tech-tag"><span class="dot"></span> &lt;iostream&gt;</div>
      <div class="tech-tag"><span class="dot"></span> &lt;iomanip&gt;</div>
      <div class="tech-tag"><span class="dot"></span> &lt;limits&gt;</div>
      <div class="tech-tag"><span class="dot"></span> 2D Arrays</div>
      <div class="tech-tag"><span class="dot"></span> Nested Loops</div>
    </div>
  </div>

  <!-- PROJECT STRUCTURE -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">📂</div>
      <div class="section-title">Project Structure</div>
      <div class="line-accent"></div>
    </div>
    <div class="file-tree">
<span class="tree-root">Final-Project-of-C-/</span>
<span class="tree-branch">│</span>
<span class="tree-branch">├── </span><span class="tree-file">matrix.cpp</span>       <span class="tree-desc">← Main C++ source file</span>
<span class="tree-branch">├── </span><span class="tree-file">README.md</span>        <span class="tree-desc">← Project documentation</span>
<span class="tree-branch">└── </span><span class="tree-file">Documents/</span>       <span class="tree-desc">← Report &amp; presentation assets</span></div>
  </div>

  <div class="divider"></div>

  <!-- FUTURE IMPROVEMENTS -->
  <div class="section">
    <div class="section-header">
      <div class="section-icon">🚀</div>
      <div class="section-title">Future Improvements</div>
      <div class="line-accent"></div>
    </div>
    <div class="future-grid">
      <div class="future-item">
        <div class="fi">➖</div>
        <div class="ft">Subtraction</div>
        <div class="fd">Matrix A − B operation</div>
      </div>
      <div class="future-item">
        <div class="fi">✖️</div>
        <div class="ft">Multiplication</div>
        <div class="fd">Dot product A × B</div>
      </div>
      <div class="future-item">
        <div class="fi">📐</div>
        <div class="ft">Dynamic Size</div>
        <div class="fd">Use vectors for any size</div>
      </div>
      <div class="future-item">
        <div class="fi">🖥</div>
        <div class="ft">GUI Version</div>
        <div class="fd">Visual graphical interface</div>
      </div>
    </div>
  </div>

  <!-- FOOTER -->
  <div class="footer">
    <div class="footer-accent"></div>
    <div class="footer-name">Sejal Singh</div>
    <div class="footer-meta">
      🎓 B.Tech — Computer Science &amp; Engineering<br>
      📅 2025 – 2029 &nbsp;·&nbsp; Case Study 167
    </div>
  </div>

</div>
</body>
</html>
