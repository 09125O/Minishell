GUIDE PRATIQUE GIT - MINISHELL

=== AVANT DE COMMENCER À CODER ===

1. Aller sur develop et la mettre à jour :
```bash
git checkout develop
git pull origin develop
```

2. Aller sur votre branche de travail :
```bash
git checkout feature/lexer    # si vous travaillez sur le lexer
# OU
git checkout feature/parser   # si vous travaillez sur le parser
# OU
git checkout feature/executor # si vous travaillez sur l'executor
# etc...
```

=== PENDANT LE DÉVELOPPEMENT ===

3. Avant de coder, vérifiez que vous êtes sur la bonne branche :
```bash
git branch    # votre branche doit avoir une étoile *
```

4. Après avoir codé, vérifiez vos modifications :
```bash
git status    # voir les fichiers modifiés en rouge
```

5. Ajouter vos modifications :
```bash
git add nom_du_fichier    # pour un fichier spécifique
# OU
git add .                 # pour tous les fichiers
```

6. Créer un commit :
```bash
git commit -m "feat(lexer): ajout fonction tokenize"
```

7. Envoyer sur GitHub :
```bash
git push origin feature/lexer    # remplacer lexer par votre feature
```

=== POUR FAIRE VALIDER VOTRE CODE ===

8. Sur GitHub :
- Aller sur le dépôt minishell
- Cliquer sur "Pull requests"
- Cliquer sur le bouton vert "New pull request"
- Sélectionner :
  - base: develop
  - compare: votre branche (feature/lexer par exemple)
- Remplir :
  - Titre : ce que vous avez fait
  - Description : détails
  - Reviewer : votre binôme
  - Milestone : la semaine en cours

=== SI VOUS AVEZ UN PROBLÈME ===

Si vous avez codé sur la mauvaise branche :
```bash
# Sauvegarder votre travail
git stash

# Aller sur la bonne branche
git checkout bonne-branche

# Récupérer votre travail
git stash pop
```

Si vous voulez annuler votre dernier commit :
```bash
git reset --soft HEAD~1
```
