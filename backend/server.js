const express = require("express");
const fs = require("fs");
const { exec } = require("child_process");

const app = express();

// ✅ CORS (simple + working)
app.use((req, res, next) => {
    res.header("Access-Control-Allow-Origin", "*");
    res.header("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    res.header("Access-Control-Allow-Headers", "Content-Type");
    if (req.method === "OPTIONS") return res.sendStatus(200);
    next();
});

app.use(express.json());

// ▶ Run C code
app.post("/run", (req, res) => {
    const code = req.body.code;

    fs.writeFileSync("program.c", code);

    exec("gcc program.c -o program && ./program", (err, stdout, stderr) => {
        if (err) return res.json({ output: stderr });
        res.json({ output: stdout });
    });
});

// Test route
app.get("/", (req, res) => {
    res.send("Backend working ✅");
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => console.log("Server running on " + PORT));