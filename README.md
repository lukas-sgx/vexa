<h1 align="center">⚡ Vexa ⚡</h1>
<p align="center">
  <b>Banque et Crypto</b>  
  <br/>  
  <img src="https://img.shields.io/badge/langage-C-blue?style=flat-square"/>
  <img src="https://img.shields.io/badge/database-SQLite-lightgrey?style=flat-square"/>
  <img src="https://img.shields.io/badge/build-Makefile-green?style=flat-square"/>
</p>

## 🚀 Fonctionnalités

- 🔑 **Authentification** via `number` + `personnal`
- 🕶️ **Saisie masquée** du mot de passe (via `termios`)
- 🛡️ **Requêtes préparées** pour éviter l’injection SQL
- 🗄️ Stockage des utilisateurs dans `account.db`
- 👨‍💻 Structure modulaire :
  - `authentication.c` → gestion du login
  - `db.c` → connexion SQLite
  - `screen.c` → saisie utilisateur & masquage
  - `main.c` → flux principal
  - `Makefile` → compilation simplifiée

---

## 📦 Installation

### Prérequis
- GCC (ou équivalent)
- SQLite3 (`libsqlite3-dev`)

```bash
# Debian/Ubuntu
sudo apt update
sudo apt install build-essential libsqlite3-dev
```

### Compilation
```bash
make all
```

### Exécution
```bash
make run
```

### Nettoyage
```bash
make clean
```

---

## 🗄 Structure du projet

```
.
├── authentication.c   # Fonctions d’authentification
├── db.c               # Connexion et requêtes SQLite
├── screen.c           # Interface terminal (scan, masquage)
├── main.c             # Point d’entrée du programme
├── Makefile           # Build & run
└── README.md          # Documentation
```

---

## 📚 Base de données

La base `account.db` doit contenir une table `account`. Exemple :

```sql
CREATE TABLE account (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  number TEXT NOT NULL UNIQUE,
  personnal TEXT NOT NULL,
  name TEXT,
  prenom TEXT
);

INSERT INTO account (number, personnal, name, prenom)
VALUES ('1234', 'secret', 'Dupont', 'Jean');
```

---

## 🖥️ Exemple d’utilisation

```text
Nom d’utilisateur (number) : 1234
Mot de passe (personnal) : ******
✅ Bienvenue Dupont Jean !
```

```text
Nom d’utilisateur (number) : 9999
Mot de passe (personnal) : ******
❌ Identifiants invalides.
```

---

## 🔒 Sécurité

- Masquage du mot de passe lors de la saisie (`termios`)
- Requêtes préparées (`sqlite3_prepare_v2` + `sqlite3_bind_text`)
- ⚠️ Mots de passe actuellement stockés **en clair**
  - 👉 Pour un vrai projet : utiliser un **hash** (bcrypt, argon2, SHA-256…)

---

## 🤝 Contribution

Les contributions sont bienvenues 🎉

- Ajouter une fonctionnalité (inscription, gestion des rôles, logs, etc.)
- Améliorer la sécurité (hashage, salage des mots de passe)
- Optimiser l’interface terminal
- Écrire des tests unitaires

---

## 📜 Licence

📌 Auteur : [lukas-sgx](https://github.com/lukas-sgx)  
Licence : MIT

---

✨ Merci d’utiliser Vexa ! ✨