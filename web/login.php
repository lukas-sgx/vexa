<?php
session_start();

require_once 'include/db.php';

if(isset($_SESSION["user"])){
	header('Location: dashboard.php');
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $user = $_POST['username'] ?? '';
    $pin  = $_POST['pin'] ?? '';

    $db = getDBConnection();

    $query = "SELECT * FROM user WHERE `number` = :username AND `personnal` = :code";
    $stmt = $db->prepare($query);
    $stmt->bindParam(':username', $user);
    $stmt->bindParam(':code', $pin);
    $stmt->execute();

    $info = $stmt->fetch(PDO::FETCH_ASSOC);

    if ($user === $info["number"] && $pin === $info["personnal"]) {
        $_SESSION['user'] = $user;
		$_SESSION['name'] = $info["name"];
		$_SESSION['ftName'] = $info["prenom"];

        header('Location: dashboard.php');
        exit;
    } else {
        $error = "Identifiants invalides";
    }
}
?>
<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <title>Vexa Bank — Login</title>
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700;800&display=swap" rel="stylesheet">
  <link rel="stylesheet" href="assets/login.css">
</head>
<body>
  <form method="post" class="card">
    
    <div class="head">
        <img src="logo.svg" class="logo" alt="" srcset="">    
        <h1>Vexa Bank</h1>
    </div>
    <?php if(!empty($error)): ?>
      <div class="error"><?php echo htmlspecialchars($error); ?></div>
    <?php endif; ?>

    <div class="field">
      <input type="text" name="username" id="username" placeholder="Account Number (11 char)" required>
    </div>
    <br>

    <div class="pin-display" id="pinDisplay">
      <div class="dot" id="d1"></div>
      <div class="dot" id="d2"></div>
      <div class="dot" id="d3"></div>
      <div class="dot" id="d4"></div>
      <div class="dot" id="d5"></div>
      <div class="dot" id="d6"></div>
    </div>

    <div class="keypad" id="keypad"></div>

    <input type="hidden" name="pin" id="pinInput">
    <button type="submit" class="btn primary" style="margin-top:16px">Se connecter</button>

  </form>

  <script>
    const keypad = document.getElementById('keypad');
    const pinInput = document.getElementById('pinInput');
    const pinDisplay = document.getElementById('pinDisplay');
    let currentPin = '';

    function shuffle(array) {
      for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
      }
      return array;
    }

    function renderKeypad(){
      const digits = shuffle(['0','1','2','3','4','5','6','7','8','9']);
      keypad.innerHTML = '';
      digits.forEach(d => {
        const btn = document.createElement('button');
        btn.type='button';
        btn.textContent = d;
        btn.addEventListener('click', ()=>{
          if(currentPin.length < 6){
            currentPin += d;
            updateDisplay();
          }
        });
        keypad.appendChild(btn);
      });
      
      const del = document.createElement('button');
      del.type='button';
      del.textContent='←';
      del.addEventListener('click', ()=>{
        currentPin = currentPin.slice(0,-1);
        updateDisplay();
      });
      keypad.appendChild(del);
    }

    function updateDisplay(){
      pinInput.value = currentPin;
      for(let i=1;i<=6;i++){
        const dot = document.getElementById('d'+i);
        if(i <= currentPin.length){
          dot.classList.add('filled');
        } else {
          dot.classList.remove('filled');
        }
      }
    }

    renderKeypad();
  </script>
</body>
</html>
