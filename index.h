const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Water Level Monitor</title>
  <style>
    :root {
      --primary: #00a8ff;
      --secondary: #0097e6;
      --bg: #f5f6fa;
      --text: #2f3640;
      --danger: #e84118;
      --success: #4cd137;
    }
    body {
      font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
      background-color: var(--bg);
      color: var(--text);
      display: flex;
      flex-direction: column;
      align-items: center;
      min-height: 100vh;
      margin: 0;
      padding: 20px;
    }
    h1 {
      margin-bottom: 10px;
      color: var(--secondary);
    }
    .card {
      background: white;
      border-radius: 20px;
      box-shadow: 0 10px 25px rgba(0,0,0,0.1);
      padding: 30px;
      width: 100%;
      max-width: 400px;
      text-align: center;
      margin-top: 20px;
    }
    .tank-container {
      width: 150px;
      height: 250px;
      border: 4px solid #dcdde1;
      border-radius: 0 0 15px 15px;
      border-top: none;
      margin: 20px auto;
      position: relative;
      background: #fff;
      overflow: hidden;
    }
    .water {
      position: absolute;
      bottom: 0;
      left: 0;
      width: 100%;
      height: 0%;
      background: linear-gradient(to top, var(--secondary), var(--primary));
      transition: height 0.5s ease-in-out;
      opacity: 0.8;
    }
    .water::after {
      content: '';
      position: absolute;
      top: -10px;
      left: 0;
      width: 100%;
      height: 20px;
      background: rgba(255,255,255,0.3);
      border-radius: 50%;
    }
    .stats {
      display: flex;
      justify-content: space-around;
      margin-top: 20px;
    }
    .stat-box {
      background: #f1f2f6;
      padding: 10px;
      border-radius: 10px;
      width: 45%;
    }
    .stat-value {
      font-size: 1.5rem;
      font-weight: bold;
      color: var(--text);
    }
    .stat-label {
      font-size: 0.8rem;
      color: #7f8fa6;
    }
    .status-indicator {
      margin-top: 15px;
      font-weight: bold;
      padding: 5px 15px;
      border-radius: 20px;
      display: inline-block;
    }
    .status-normal { background: #d1fae5; color: #065f46; }
    .status-warning { background: #fee2e2; color: #991b1b; }
    
    /* Wave Animation */
    @keyframes wave {
      0% { transform: translateX(-50%) rotate(0deg); }
      50% { transform: translateX(-50%) rotate(180deg); }
      100% { transform: translateX(-50%) rotate(360deg); }
    }
  </style>
</head>
<body>

  <h1>💧 Water Monitor</h1>
  
  <div class="card">
    <div class="tank-container">
      <div class="water" id="waterLevel"></div>
    </div>
    
    <div id="statusText" class="status-indicator status-normal">Normal Level</div>

    <div class="stats">
      <div class="stat-box">
        <div class="stat-value" id="percentage">0%</div>
        <div class="stat-label">Level</div>
      </div>
      <div class="stat-box">
        <div class="stat-value"><span id="distance">0</span> cm</div>
        <div class="stat-label">Distance</div>
      </div>
    </div>
  </div>

  <script>
    function updateData() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          const level = data.level;
          const distance = data.distance;
          
          // Update text
          document.getElementById('percentage').innerText = level + '%';
          document.getElementById('distance').innerText = distance;
          
          // Update visual tank
          document.getElementById('waterLevel').style.height = level + '%';
          
          // Update status
          const statusEl = document.getElementById('statusText');
          if (level > 90) {
            statusEl.innerText = "⚠️ Overflow Risk";
            statusEl.className = "status-indicator status-warning";
          } else if (level < 10) {
            statusEl.innerText = "⚠️ Low Water";
            statusEl.className = "status-indicator status-warning";
          } else {
            statusEl.innerText = "✅ Normal Level";
            statusEl.className = "status-indicator status-normal";
          }
        })
        .catch(error => console.error('Error fetching data:', error));
    }

    // Update every 2 seconds
    setInterval(updateData, 2000);
    updateData(); // Initial call
  </script>
</body>
</html>
)=====";
