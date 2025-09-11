<?php
session_start();
/*
  Aurora Bank — Page d'accueil (index.php)
  -------------------------------------------------
  - Placez ce fichier dans le même dossier que votre login.php.
  - Pour afficher les initiales de l'utilisateur (avatar), définissez $_SESSION['fullname'] lors du login, par exemple :
      $_SESSION['user'] = $user;
      $_SESSION['fullname'] = 'Jean Sebastien';
*/

function getInitials($name) {
    $name = trim(preg_replace('/\s+/', ' ', $name));
    if ($name === '') return '';
    $parts = preg_split('/[\s-]+/', $name);
    $initials = '';
    foreach ($parts as $p) {
        $p = trim($p);
        if ($p !== '') {
            $initials .= mb_strtoupper(mb_substr($p, 0, 1, 'UTF-8'), 'UTF-8');
        }
    }
    return mb_substr($initials, 0, 2, 'UTF-8');
}

$logged = isset($_SESSION['user']);
$fullname = $_SESSION['fullname'] ?? $_SESSION['user'] ?? '';
$initials = $logged ? getInitials($fullname) : '';
?>
<!doctype html>
<html lang="fr">
<head>
  <meta charset="utf-8" />
  <meta name="viewport" content="width=device-width,initial-scale=1" />
  <meta name="description" content="Aurora Bank — banque en ligne moderne, sécurisée et sans frontières." />
  <title>Aurora Bank — Banque en ligne</title>
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700;800&display=swap" rel="stylesheet">
  <style>
    :root{
      --bg:#071025;
      --glass: rgba(255,255,255,0.03);
      --muted:#9aa6b2;
      --accent1:#60a5fa;
      --accent2:#7c3aed;
      --radius:14px;
    }
    *{box-sizing:border-box}
    body{margin:0;font-family:Inter, system-ui, -apple-system, 'Segoe UI', Roboto, Arial;background:radial-gradient(900px 300px at 10% 10%, rgba(124,58,237,0.08), transparent), radial-gradient(700px 260px at 90% 90%, rgba(96,165,250,0.04), transparent),var(--bg);color:#e6eef6;-webkit-font-smoothing:antialiased}
    header{display:flex;align-items:center;justify-content:space-between;padding:20px;max-width:1200px;margin:0 auto}
    .brand{display:flex;align-items:center;gap:12px}
    .logo{width:48px;height:48px;border-radius:12px;display:flex;align-items:center;justify-content:center;font-weight:800;color:#001018}
    nav{display:flex;gap:18px;align-items:center}
    nav a{color:var(--muted);text-decoration:none;font-weight:600}
    .btn{padding:10px 14px;border-radius:10px;border:0;cursor:pointer;font-weight:700}
    .btn.cta{background:linear-gradient(90deg,var(--accent1),var(--accent2));color:#001018}
    .btn.ghost{background:var(--glass);color:var(--muted)}

    /* Hero */
    .hero{max-width:1200px;margin:28px auto;padding:28px;display:grid;grid-template-columns:1fr 420px;gap:24px;align-items:center}
    .hero-card{padding:28px;border-radius:16px;background:linear-gradient(180deg, rgba(255,255,255,0.02), rgba(255,255,255,0.01));box-shadow:0 10px 30px rgba(2,6,23,0.6)}
    h1{margin:0;font-size:36px;line-height:1.05}
    p.lead{color:var(--muted);margin-top:12px;margin-bottom:18px}
    .kpis{display:flex;gap:12px;margin-top:18px}
    .kpi{background:var(--glass);padding:12px;border-radius:12px;text-align:center;flex:1}
    .kpi strong{display:block;font-size:18px}

    /* Features */
    .features{max-width:1200px;margin:18px auto;padding:0 28px 48px;display:grid;grid-template-columns:repeat(3,1fr);gap:18px}
    .feature{background:linear-gradient(180deg, rgba(255,255,255,0.02), rgba(255,255,255,0.01));padding:18px;border-radius:12px}
    .feature h3{margin:0 0 8px}
    .feature p{margin:0;color:var(--muted)}

    footer{max-width:1200px;margin:0 auto;padding:28px;color:var(--muted);display:flex;justify-content:space-between;align-items:center}

    /* Responsive */
    @media (max-width:980px){
      .hero{grid-template-columns:1fr}
      .features{grid-template-columns:1fr 1fr}
      nav{display:none}
    }
    @media (max-width:520px){
      .features{grid-template-columns:1fr}
      header{padding:12px}
      .hero{padding:12px}
    }

    /* avatar */
    .avatar{width:44px;height:44px;border-radius:10px;background:linear-gradient(135deg,var(--accent2),var(--accent1));display:flex;align-items:center;justify-content:center;color:#001018;font-weight:800}
  </style>
</head>
<body>

  <header>
    <div class="brand">
      <img src="logo.svg" class="logo" height="50px">
      <div>
        <div style="font-weight:700">Aurora Bank</div>
        <div style="font-size:12px;color:var(--muted)">banque en ligne — prototype</div>
      </div>
    </div>

    <nav aria-label="Navigation principale">
      <a href="#features">Fonctionnalités</a>
      <a href="#security">Sécurité</a>
      <a href="#tarifs">Tarifs</a>
      <?php if($logged): ?>
        <a href="dashboard.php" class="btn ghost">Tableau de bord</a>
        <a href="logout.php" class="btn" style="margin-left:8px;">Se déconnecter</a>
        <div style="margin-left:12px" title="<?=htmlspecialchars($fullname)?>">
          <div class="avatar"><?=htmlspecialchars($initials)?></div>
        </div>
      <?php else: ?>
        <a href="login.php" class="btn ghost">Se connecter</a>
        <a href="signup.php" class="btn cta">Ouvrir un compte</a>
      <?php endif; ?>
    </nav>
  </header>

  <main>
    <section class="hero">
      <div class="hero-card">
        <h1>La banque moderne qui tient dans votre poche</h1>
        <p class="lead">Comptes courants, cartes internationales, épargne intelligente et sécurité bancaire de niveau bancaire — simple, rapide, transparent.</p>

        <div style="display:flex;gap:12px">
          <a href="signup.php" class="btn cta">Ouvrir un compte</a>
          <a href="login.php" class="btn ghost">Se connecter</a>
        </div>

        <div class="kpis">
          <div class="kpi"><small>Clients</small><strong>120k+</strong></div>
          <div class="kpi"><small>Évaluations</small><strong>4.7 ★</strong></div>
          <div class="kpi"><small>Pays</small><strong>25</strong></div>
        </div>
      </div>

      <aside style="display:flex;flex-direction:column;gap:12px">
        <div style="padding:18px;border-radius:12px;background:linear-gradient(135deg, rgba(96,165,250,0.06), rgba(124,58,237,0.06));">
          <div style="font-size:12px;color:var(--muted)">Solde exemple</div>
          <div style="font-weight:800;font-size:20px;margin-top:6px">€ 8,420.50</div>
          <div style="margin-top:12px"><small class="muted">Carte • AUR **** 4312</small></div>
        </div>

        <div style="padding:18px;border-radius:12px;background:var(--glass)">
          <div style="font-size:12px;color:var(--muted)">Taux de change</div>
          <div style="font-weight:700;margin-top:6px">1 EUR = 1.06 USD</div>
          <div style="font-size:12px;color:var(--muted);margin-top:8px">Dernière mise à jour: 07 Sep 2025</div>
        </div>
      </aside>
    </section>

    <section id="features" class="features">
      <div class="feature">
        <h3>Compte courant moderne</h3>
        <p>Gestion instantanée, notifications en temps réel, IBAN européen et transferts rapides.</p>
      </div>
      <div class="feature">
        <h3>Cartes & paiements internationaux</h3>
        <p>Cartes physiques et virtuelles, paiements sans frais cachés avec conversion au meilleur taux.</p>
      </div>
      <div class="feature">
        <h3>Épargne intelligente</h3>
        <p>Arrondis automatiques, objectifs d'épargne et épargnes programmées.</p>
      </div>
      <div class="feature">
        <h3>Sécurité bancaire</h3>
        <p>Authentification forte, chiffrement des données et surveillance anti-fraude 24/7.</p>
      </div>
      <div class="feature">
        <h3>Support client</h3>
        <p>Chat en direct, assistance multilingue et centre d'aide complet.</p>
      </div>
      <div class="feature">
        <h3>API & intégrations</h3>
        <p>Connectez vos outils (compta, ERP) via notre API sécurisée et simple d'utilisation.</p>
      </div>
    </section>

    <section id="security" style="max-width:1200px;margin:0 auto;padding:0 28px 48px;">
      <div style="display:flex;gap:18px;align-items:center;background:linear-gradient(180deg, rgba(255,255,255,0.02), rgba(255,255,255,0.01));padding:18px;border-radius:12px;">
        <div style="flex:1">
          <h3>Sécurité & conformité</h3>
          <p style="color:var(--muted)">Nous utilisons les standards de l'industrie (chiffrement AES-256, HSM pour les clés, surveillance active). Vos données et votre argent bénéficient d'un niveau de protection élevé.</p>
        </div>
        <div style="width:260px;text-align:center">
          <div style="font-weight:800;font-size:20px">KYC & AML</div>
          <div style="color:var(--muted);margin-top:8px">Processus de vérification simple et rapide pour garantir la sécurité de tous.</div>
        </div>
      </div>
    </section>

    <section id="tarifs" style="max-width:1200px;margin:0 auto;padding:0 28px 48px;">
      <h3 style="margin-top:0">Tarifs</h3>
      <div style="display:flex;gap:18px;flex-wrap:wrap">
        <div style="flex:1;min-width:240px;background:var(--glass);padding:16px;border-radius:12px">
          <strong>Compte gratuit</strong>
          <div style="color:var(--muted);margin-top:8px">Comptes courants, carte standard, transferts SEPA gratuits.</div>
        </div>
        <div style="flex:1;min-width:240px;background:linear-gradient(90deg,var(--accent1),var(--accent2));padding:16px;border-radius:12px;color:#001018">
          <strong>Premium</strong>
          <div style="margin-top:8px">Avantages: carte premium, assurances voyage, limite augmentée.</div>
        </div>
      </div>
    </section>
  </main>

  <footer>
    <div>© <?=date('Y')?> Vexa Bank</div>
    <div style="display:flex;gap:12px"><a href="#" style="color:var(--muted);text-decoration:none">CGU</a><a href="#" style="color:var(--muted);text-decoration:none">Politique de confidentialité</a></div>
  </footer>

  <script>
    // smooth scroll pour les ancres
    document.querySelectorAll('a[href^="#"]').forEach(a=>{
      a.addEventListener('click', function(e){
        e.preventDefault();
        const id = this.getAttribute('href').slice(1);
        const el = document.getElementById(id);
        if(el) el.scrollIntoView({behavior:'smooth',block:'start'});
      });
    });
  </script>
</body>
</html>
