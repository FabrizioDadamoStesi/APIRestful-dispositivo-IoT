<?php

// Indirizzo IP di NodeMCU
$nodemcu_ip = "192.168.1.100";

// Rotta dell'API RESTful per ottenere la temperatura
$api_route = "/api/temperature";

// URL completo dell'API RESTful
$url = "http://" . $nodemcu_ip . $api_route;

// Effettua una richiesta HTTP GET all'API RESTful di NodeMCU
$response = file_get_contents($url);

// Decodifica la risposta JSON restituita dall'API RESTful di NodeMCU
$data = json_decode($response, true);

// Mostra la temperatura in una pagina web
echo "La temperatura attuale è " . $data['temperature'] . "°C";

?>
