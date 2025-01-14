
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>LoRa-ESP32 Sensor Monitoring Project</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            line-height: 1.6;
            margin: 0;
            padding: 0;
            background-color: #f4f4f9;
            color: #333;
        }
        header {
            background: #0078d4;
            color: white;
            padding: 1rem 2rem;
            text-align: center;
        }
        header h1 {
            margin: 0;
            font-size: 2.5rem;
        }
        section {
            padding: 2rem;
            margin: 2rem auto;
            max-width: 900px;
            background: white;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
        }
        h2 {
            color: #0078d4;
            margin-bottom: 1rem;
        }
        p {
            margin-bottom: 1rem;
        }
        img {
            display: block;
            max-width: 100%;
            margin: 1rem auto;
            border-radius: 8px;
            border: 1px solid #ddd;
        }
        ul {
            margin: 1rem 0;
            padding-left: 1.5rem;
        }
        ul li {
            margin-bottom: 0.5rem;
        }
        footer {
            text-align: center;
            padding: 1rem;
            margin-top: 2rem;
            background: #0078d4;
            color: white;
        }
    </style>
</head>
<body>

<header>
    <h1>LoRa-ESP32 Sensor Monitoring Project</h1>
</header>

<section>
    <h2>Overview</h2>
    <p>This project utilizes LoRa and ESP32 modules to monitor soil humidity and temperature from a remote farm and display the data live on a mobile application. The LoRa transmitter collects sensor data and sends it to the LoRa receiver, which is connected to an ESP32 module acting as a Wi-Fi access point.</p>
</section>

<section>
    <h2>Features</h2>
    <ul>
        <li>Real-time monitoring of soil humidity and temperature.</li>
        <li>LoRa-based long-distance communication.</li>
        <li>ESP32 acts as a Wi-Fi access point to display live data on a mobile app.</li>
        <li>Easy to set up and deploy in remote environments.</li>
    </ul>
</section>

<section>
    <h2>Connection Diagram</h2>
    <p>The following diagram illustrates the connection setup for the LoRa receiver and ESP32:</p>
    <img src="connection-diagram.png" alt="Connection Diagram for LoRa and ESP32">
</section>

<section>
    <h2>Setup Instructions</h2>
    <ol>
        <li>Connect the LoRa module to the ESP32 as per the connection diagram.</li>
        <li>Flash the provided receiver code to the ESP32 module.</li>
        <li>Power the LoRa and ESP32 module using a 5V power source.</li>
        <li>Connect your mobile phone to the ESP32 Wi-Fi network (SSID: <code>ESP32_LoRa_Receiver</code>, Password: <code>123456789</code>).</li>
        <li>Access the live data through the app or a browser using the IP address <code>192.168.4.1</code>.</li>
    </ol>
</section>

<section>
    <h2>Usage</h2>
    <p>After completing the setup, the ESP32 will display live data received from the LoRa transmitter. The mobile app will fetch this data from the ESP32 and present it in an intuitive interface.</p>
</section>

<section>
    <h2>License</h2>
    <p>This project is open source and available under the MIT License.</p>
</section>

<footer>
    <p>© 2025 LoRa-ESP32 Sensor Monitoring Project | Designed for GitHub</p>
</footer>

</body>
</html>
