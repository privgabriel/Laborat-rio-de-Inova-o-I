import React, { useState, useEffect } from "react";
import axios from "axios";

function App() {
  const [data, setData] = useState({
    distancia: "Carregando...",
  });

  const fetchData = async () => {
    try {
      const response = await axios.get("http://10.0.2.130:3000/data"); // Substitua localhost pelo IP correto
      setData(response.data);
    } catch (error) {
      console.error("Erro ao buscar dados:", error); // Adicionado console.log para debugging
      setData({ distancia: "Erro ao carregar dados" });
    }
  };

  useEffect(() => {
    fetchData();
    const interval = setInterval(fetchData, 5000); // Atualiza a cada 10 segundos
    return () => clearInterval(interval);
  }, []);

  return (
    <div style={styles.container}>
      <div style={styles.card}>
        <h1 style={styles.title}>Distância Monitorada</h1>
        <p style={styles.distance}>{data.distancia} cm</p>
        <p style={styles.updateInfo}>Atualizado a cada 10 segundos</p>
      </div>
    </div>
  );
}

const styles = {
  container: {
    display: "flex",
    justifyContent: "center",
    alignItems: "center",
    height: "100vh",
    backgroundColor: "#f0f0f0",
  },
  card: {
    backgroundColor: "#ffffff",
    borderRadius: "10px",
    padding: "30px",
    boxShadow: "0px 4px 12px rgba(0, 0, 0, 0.1)",
    textAlign: "center",
  },
  title: {
    fontSize: "1.8em",
    marginBottom: "15px",
    color: "#333",
  },
  distance: {
    fontSize: "3em",
    fontWeight: "bold",
    color: "#4CAF50",
    marginBottom: "10px",
  },
  updateInfo: {
    fontSize: "0.9em",
    color: "#999",
  },
};

export default App;
