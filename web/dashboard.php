<?php session_start();

require_once 'include/screen.php';

if(!isset($_SESSION["user"])){
	header('Location: login.php');
}
?>

<!doctype html>
<html lang="fr">
<head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width,initial-scale=1" />
    <title>Vexa Bank</title>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700;800&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="assets/style.css">
</head>
<body>
  <div class="layout">
    <aside class="sidebar" aria-label="Navigation">
      <div class="brand">
        <div class="logo"><img src="logo.svg" class="logo-svg" alt="" srcset=""></div>
        <div>
          <h1>Vexa</h1>
          <p>Banque en ligne</p>
        </div>
      </div>

      <nav>
        <div class="nav-item active" data-nav="dashboard">
          <svg width="18" height="18" viewBox="0 0 24 24" fill="none"><path d="M3 13h8V3H3v10zM3 21h8v-6H3v6zM13 21h8V11h-8v10zM13 3v6h8V3h-8z" fill="currentColor"/></svg>
          <span>Tableau de bord</span>
        </div>
        <div class="nav-item" data-nav="payments">
          <svg width="18" height="18" viewBox="0 0 24 24" fill="none"><path d="M21 7H3V5h18v2zM3 19h18v-8H3v8z" fill="currentColor"/></svg>
          <span>Paiements</span>
        </div>
        <div class="nav-item" data-nav="cards">
          <svg width="18" height="18" viewBox="0 0 24 24" fill="none"><path d="M3 7h18v11H3zM3 3h18v2H3z" fill="currentColor"/></svg>
          <span>Cartes</span>
        </div>
        <div class="nav-item" data-nav="settings">
          <svg width="18" height="18" viewBox="0 0 24 24" fill="none"><path d="M12 8.59A3.41 3.41 0 1015.41 12 3.41 3.41 0 0012 8.59zM4 12a8.05 8.05 0 01.6-3L2 7l2-3 2.6 1A8 8 0 0112 4a8 8 0 013.4 0L17 3l2 3-2.6 2A8.05 8.05 0 0120 12a8.05 8.05 0 01-.6 3l2.6 2-2 3-2.6-1A8 8 0 0112 20a8 8 0 01-3.4 0L7 21 5 18l2.6-2A8.05 8.05 0 014 12z" fill="currentColor"/></svg>
          <span>Paramètres</span>
        </div>
      </nav>

      <div class="user-pane">
        <div class="avatar"><?php 
          $nomComplet = $_SESSION["ftName"]." ".$_SESSION["name"];
          echo $initiales = implode('', array_map(fn($w) => strtoupper($w[0]), explode(' ', $nomComplet)));?>
        </div>
        <div class="user-meta">
          <strong><?php echo $_SESSION["ftName"]." ".$_SESSION["name"];?></strong>
          <small>Compte basic • EUR</small>
        </div>
      </div>
    </aside>

    <main class="main">
      <div class="topbar card">
        <div style="display:flex;align-items:center;gap:12px">
          <button class="btn" aria-label="Open menu">☰</button>
          <div style="display:flex;align-items:center;gap:12px">
            <div style="font-weight:700">Bonjour, <?php echo $_SESSION["ftName"]." ".$_SESSION["name"];?></div>
            <div class="search" role="search">
              <svg width="16" height="16" viewBox="0 0 24 24" fill="none"><path d="M21 21l-4.35-4.35" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/></svg>
              <input placeholder="Rechercher une transaction, bénéficiaire..." aria-label="Rechercher" />
            </div>
          </div>
        </div>

        <div class="actions">
          <button class="btn">Aide</button>
          <button class="btn">Notifications</button>
          <button class="btn primary" id="openTransfer">Envoyer</button>
        </div>
      </div>

      <section class="grid">
        <div>
          <div class="card account-card">
            <div style="display:flex;justify-content:space-between;align-items:center">
              <div>
                <small>Solde disponible</small>
                <?php $solde = getSolde($_SESSION["user"]); 
                    if($solde >= 0){
                        echo("<h2 style='color: var(--success)'>€ ".$solde."</h2>");
                    }else{
                    	echo("<h2 style='color: var(--danger)'>€ ".$solde."</h2>");
                    }
				?>
                <small class="muted">IBAN: <?php echo getIBAN($_SESSION["user"]); ?></small>
              </div>
              <div style="text-align:right">
                <div style="font-size:12px;color:var(--muted)">Carte</div>
                <div style="margin-top:8px;background:linear-gradient(135deg,#60a5fa,#7c3aed);padding:12px;border-radius:10px;min-width:160px;color:#001018;font-weight:700">VEX • **** 4312</div>
              </div>
            </div>

            <div class="card-actions">
              <button class="btn primary" id="quickPay">Payer</button>
              <button class="btn" id="quickRequest">Demander</button>
              <button class="btn" id="quickExchange">Convertir</button>
            </div>

            <div style="display:flex;justify-content:space-between;gap:12px;margin-top:6px">
              <div style="flex:1">
                <div style="font-size:12px;color:var(--muted)">Dépenses ce mois</div>
                <div style="font-weight:700">€ 1,230</div>
                <div class="progress" style="margin-top:8px"><i></i></div>
              </div>
              <div style="flex:1">
                <div style="font-size:12px;color:var(--muted)">Épargne</div>
                <div style="font-weight:700">€ 4,350</div>
                <div class="progress" style="margin-top:8px"><i style="width:52%"></i></div>
              </div>
            </div>
          </div>

          <div class="card" style="margin-top:18px">
            <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:8px">
              <div><strong>Transactions récentes</strong><div style="font-size:12px;color:var(--muted)">Les 7 derniers jours</div></div>
              <div style="font-size:12px;color:var(--muted)">Voir tout</div>
            </div>

            <div class="transactions" id="txlist">
              <!-- transactions via JS -->
            </div>
          </div>
        </div>

        <aside class="right">
          <div class="card mini-card">
            <div>
              <div style="font-size:12px;color:var(--muted)">Budget voyage</div>
              <div style="font-weight:700">€ 1,800 / € 2,500</div>
            </div>
            <div style="width:110px">
              <div class="progress" style="height:12px"><i style="width:72%"></i></div>
            </div>
          </div>

          <div class="card mini-card" style="margin-top:12px">
            <div>
              <div style="font-size:12px;color:var(--muted)">Taux EUR → USD</div>
              <div style="font-weight:700">1 EUR = 1.06 USD</div>
            </div>
            <div style="font-size:13px;color:var(--muted);text-align:right">
              <div>Dernière mise à jour</div>
              <div style="font-weight:700">07 Sep 2025</div>
            </div>
          </div>

          <div class="card" style="margin-top:12px">
            <div style="display:flex;justify-content:space-between;align-items:center">
              <div>
                <strong>Économies intelligentes</strong>
                <div style="font-size:12px;color:var(--muted)">Automatisez vos arrondis</div>
              </div>
              <div style="font-size:22px;font-weight:700">€ 4,350</div>
            </div>
            <div style="margin-top:10px;font-size:13px;color:var(--muted)">Prochain versement: 15 Sep 2025</div>
          </div>

        </aside>
      </section>
    </main>
  </div>

  <!-- Modal transfer -->
  <div class="modal" id="modal">
    <div class="dialog" role="dialog" aria-modal="true" aria-labelledby="dialogTitle">
      <h3 id="dialogTitle">Envoyer de l'argent</h3>
      <p style="color:var(--muted);margin-top:6px;margin-bottom:12px">Envoyer instantanément à un bénéficiaire ou par IBAN.</p>

      <div class="field">
        <label>Montant (EUR)</label>
        <input id="amount" type="number" placeholder="€ 250" />
      </div>

      <div class="field">
        <label>Bénéficiaire</label>
        <select id="beneficiary">
          <option value="mari">Marie Dupont — 0688 998 112</option>
          <option value="pierre">Pierre Martin — IBAN</option>
          <option value="iban">Nouveau bénéficiaire (IBAN)</option>
        </select>
      </div>

      <div class="field" id="ibanField" style="display:none">
        <label>IBAN</label>
        <input id="iban" placeholder="FR76 0000 0000 0000 0000 0000 000" />
      </div>

      <div style="display:flex;gap:8px;justify-content:flex-end;margin-top:6px">
        <button class="btn" id="cancel">Annuler</button>
        <button class="btn primary" id="confirm">Confirmer</button>
      </div>

      <div class="footer-note">Paiement instantané • Frais: 0.00€</div>
    </div>
  </div>

  <script>
    const transactions = [
      <?php lastTransactions(getIBAN($_SESSION["user"])); ?>
    ];

    const txlist = document.getElementById('txlist');
    function renderTx(){
      txlist.innerHTML = '';
      transactions.forEach(tx=>{
        const el = document.createElement('div'); el.className='tx';
        el.innerHTML = `
          <div class="left">
            <div class="chip">${tx.who.split(' ')[0].slice(0,2).toUpperCase()}</div>
            <div>
              <div style="font-weight:700">${tx.who}</div>
              <small>${tx.date}</small>
            </div>
          </div>
          <div style="text-align:right">
            <div style="font-weight:700">${tx.amount < 0 ? '-' : '+'} ${Math.abs(tx.amount).toFixed(2)}€</div>
            <small style="color:${tx.amount < 0 ? 'var(--danger)' : 'var(--success)'}">${tx.amount < 0 ? 'Débit' : 'Crédit'}</small>
          </div>
        `;
        txlist.appendChild(el);
      })
    }
    renderTx();

    // --- Modal logic ---
    const modal = document.getElementById('modal');
    const openBtn = document.getElementById('openTransfer');
    const cancel = document.getElementById('cancel');
    const beneficiary = document.getElementById('beneficiary');
    const ibanField = document.getElementById('ibanField');
    const confirm = document.getElementById('confirm');

    openBtn.addEventListener('click', ()=> modal.classList.add('open'));
    cancel.addEventListener('click', ()=> modal.classList.remove('open'));
    modal.addEventListener('click', (e)=>{ if(e.target===modal) modal.classList.remove('open') });

    beneficiary.addEventListener('change', ()=>{
      if(beneficiary.value==='iban') ibanField.style.display='block'; else ibanField.style.display='none';
    });

    confirm.addEventListener('click', ()=>{
      const amount = parseFloat(document.getElementById('amount').value) || 0;
      if(amount <= 0){
        alert('Indiquez un montant supérieur à 0');
        return;
      }
      // Simuler l'envoi
      const name = beneficiary.options[beneficiary.selectedIndex].text.split('—')[0].trim();
      transactions.unshift({id:Date.now(), who:`Envoi — ${name}`, date: new Date().toISOString().slice(0,10), amount: -amount});
      renderTx();
      modal.classList.remove('open');
      // petite notification visuelle
      const tmp = document.createElement('div');
      tmp.style.cssText = 'position:fixed;right:24px;bottom:24px;background:linear-gradient(90deg,#60a5fa,#7c3aed);padding:12px 16px;border-radius:12px;color:#001018;font-weight:700;box-shadow:0 10px 30px rgba(124,58,237,0.16)';
      tmp.textContent = `Envoyé: € ${amount.toFixed(2)}`;
      document.body.appendChild(tmp);
      setTimeout(()=>tmp.remove(),2500);
    });

    // Quick actions (hooks)
    document.getElementById('quickPay').addEventListener('click', ()=>{ openBtn.click(); document.getElementById('amount').value = '' });

    // Small UX: keyboard escape closes modal
    window.addEventListener('keydown', (e)=>{ if(e.key==='Escape') modal.classList.remove('open') });

    // tiny accessibility: focus trap when modal open (simplified)
    modal.addEventListener('keydown', (e)=>{
      if(e.key==='Tab'){
        const focusables = modal.querySelectorAll('input,select,button');
        const first = focusables[0], last = focusables[focusables.length-1];
        if(e.shiftKey && document.activeElement === first){ e.preventDefault(); last.focus(); }
        else if(!e.shiftKey && document.activeElement === last){ e.preventDefault(); first.focus(); }
      }
    });

  </script>
</body>
</html>