<h1 align="center">⚡ Vexa ⚡</h1>
<p align="center">
  <b>Banque et Crypto en C</b>  
  <br/>  
  <img src="https://img.shields.io/badge/langage-C-blue?style=flat-square"/>
  <img src="https://img.shields.io/badge/database-MySQL-lightgrey?style=flat-square"/>
  <img src="https://img.shields.io/badge/build-Makefile-green?style=flat-square"/>
</p>

## 🚀 Fonctionnalités

- 🔑 Authentification via `number` + `personnal`
- 🕶️ Saisie masquée du mot de passe (via `termios`)
- 🛡️ Requêtes préparées (`mysql_stmt_prepare`) → protection contre l’injection SQL
- 💸 Transferts sécurisés (transaction MySQL)
- 🗄️ Stockage MySQL avec tables `user` et `transactions`
- 👨‍💻 Structure modulaire :
  - `authentication.c` → gestion du login et des actions
  - `db.c` → connexion MySQL et requêtes
  - `screen.c` → interface terminal (scan, masquage)
  - `main.c` → point d’entrée du programme
  - `Makefile` → compilation simplifiée

## 📦 Installation

### Prérequis
- GCC ou équivalent
- MySQL + client de développement (`libmysqlclient-dev`)

```bash
sudo apt update
sudo apt install build-essential libmysqlclient-dev
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

## 🗄 Structure du projet

```
.
├── authentication.c   # Fonctions d’authentification
├── db.c               # Connexion et requêtes MySQL
├── screen.c           # Interface terminal (scan, masquage)
├── main.c             # Point d’entrée
├── Makefile           # Build & run
└── README.md          # Documentation
```

## 📚 Base de données

Tables minimales `user` et `transactions` :
```sql
CREATE TABLE user (
  id INT AUTO_INCREMENT PRIMARY KEY,
  number VARCHAR(50) NOT NULL UNIQUE,
  personnal VARCHAR(255) NOT NULL,
  iban VARCHAR(34) NOT NULL UNIQUE,
  solde DECIMAL(15,2) DEFAULT 0
);

CREATE TABLE transactions (
  id INT AUTO_INCREMENT PRIMARY KEY,
  fromAcc VARCHAR(34),
  toAcc VARCHAR(34),
  price DECIMAL(15,2),
  type VARCHAR(50),
  date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
```

## 🖥️ Exemple d’utilisation

```text
Account Number > 1234
Personnal Code > ******

✅ Connexion réussie !

> balance
Remaining Balance: 1000.00€

> transfert 200 FR7619106006002000000000029
Tranfert approved: 200€

> balance
Remaining Balance: 800.00€
```

## 🔒 Sécurité

- Masquage du mot de passe (`termios`)
- Requêtes préparées (`mysql_stmt_bind_param`)
- Transactions MySQL pour cohérence des transferts  
- ⚠️ Mots de passe stockés **en clair** (à sécuriser avec hashage bcrypt/argon2)

## 🤝 Contribution

- Ajouter inscription d’utilisateurs
- Améliorer la sécurité
- Optimiser interface terminal
- Ajouter tests unitaires

## 📜 Licence

Auteur : [lukas-sgx](https://github.com/lukas-sgx)  
Licence : MIT

✨ Merci d’utiliser Vexa ! ✨
