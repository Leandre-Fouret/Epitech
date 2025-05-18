# 🧠 Projet Corewar

Bienvenue dans le projet **Corewar**, digne héritier du projet **RoboFactory** 🤖.  
Ce projet met en scène une bataille épique entre plusieurs programmes appelés **champions** !

---

## ⚙️ Principe du Jeu

Le jeu repose sur un **simulateur d’arène** dans lequel s’affrontent plusieurs champions compilés sous forme de fichiers `.cor`.

### 🎮 Déroulement du Jeu

- Le programme nécessite **au minimum deux champions** pour pouvoir démarrer.
- Chaque champion exécute ses instructions **à tour de rôle**, selon un cycle déterminé.
- Les champions peuvent :
  - Se déplacer 🧭
  - Modifier la mémoire partagée 💾
  - Tenter de **saboter** les autres programmes 💥

L’objectif est simple : **survivre le plus longtemps possible** 🧬  
👉 Le **dernier champion encore en vie** remporte la partie !

---

## 🗂️ Structure du Projet

- Les fichiers `.cor` sont des **champions compilés** à partir de leur code source en assembleur.
- Le cœur du programme se charge de :
  - Charger les champions dans la mémoire virtuelle.
  - Gérer les cycles d’exécution.
  - Détecter les interactions et les conflits.
  - Déterminer le **vainqueur** à la fin de la simulation.

---

## 📦 Usage

Voici comment utiliser le binaire `corewar` en ligne de commande :

```bash
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...

---

## 🖥️ Interface Graphique (Bonus)

Une **interface graphique** est disponible ! Elle permet de **visualiser le déroulement de la bataille** entre les champions. Cependant, elle est **moins stable** que la version console.

### 🧪 Pour l’activer :
Compile le projet dans le dossier `/bonus` :

```bash
cd bonus
make

