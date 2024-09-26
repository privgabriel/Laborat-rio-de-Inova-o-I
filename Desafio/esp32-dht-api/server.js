const express = require("express");
const cors = require("cors");
const app = express();

app.use(cors());
app.use(express.json());

let sensorData = {
  distancia: null,    
};

// Endpoint para receber os dados do ESP32
app.post("/data", (req, res) => {
  const { distancia } = req.body;
  
  if (distancia !== undefined && typeof distancia === 'number') {
    sensorData = { distancia };
    console.log(`Dados recebidos: Distância: ${distancia} cm`);
    res.status(200).json({ message: "Dados recebidos com sucesso", data: sensorData });
  } else {
    res.status(400).json({ message: "Dados inválidos. Verifique o formato e tente novamente." });
  }
});

// Endpoint para fornecer os dados atuais do sensor
app.get("/data", (req, res) => {
  res.status(200).json(sensorData);
});

// Inicia o servidor na porta 3000
app.listen(3000, () => {
  console.log("API rodando na porta 3000");
});
