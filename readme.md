# TI301 – Algorithmique et structures de données 2 – Projet
## Générateur automatique de phrases
_________________
[![GITHUB][git-logo]][git-url]
[![GITHUB][efrei-logo]][efrei-url]
_________________
## Présentation

>Ce projet s’inscrit dans le cadre de notre cours de « TI301 - Algorithmique et structure de données 2 » dispensé lors du Semestre 3 de notre formation à EFREI Paris.
>
>L’objectif de ce projet est de créer un programme qui génère automatiquement des phrases grammaticalement et (dans la mesure du possible) orthographiquement correctes, mais qui n'ont pas forcément de sens dans l’esprit du jeu "Cadavre exquis" inventé par l'école surréaliste en 1925
>
>Le cahier des charges de ce projet est accessible via le fichier `Generateur_automatique_de_phrases.pdf`  
_________________
## Auteurs
>Les contributeurs sur ce projet sont :
>- Maël Aubert
>- Marius Chevailler
>- Amna Boulouha
_________________
## Installation
>Ouvrez le fichier `projet_SSD2_MaëlA_MariusC_AmnaB.exe`  
>Ou compilez le code fournis et lancez l'executable généré.

>> **ATTENTION !**
>
>>Ne lancez pas le code depuis la console Clion, car elle ne prends pas en charge certaines fonctionnalités que nous avons ajouté.
>>
>>(Notamment l'effacement de la console, qui empeche le code de fonctionner correctement sur Clion)
>>
>>Utilisez plutot le powershell Windows ou lancez depuis l'executable.
>
>> Ce programme utilise des fonctions de la bibliothèque `windows.h` et par conséquent n'est utilisable que sur Windows.
_________________

Github
---------------


>Pour ce projet nous avons organisé notre code sur git.  
>
>>Le dépot est accessible via ce [lien]([git-url])

<!-- MARKDOWN LINKS & IMAGES -->
[git-url]: https://github.com/maelaubert56/PROJET_L2_SDD2_GEN_PHRASES
[git-logo]: https://img.shields.io/badge/Github-9254AD?logo=github
[efrei-url]: https://efrei.fr
[efrei-logo]: https://img.shields.io/badge/EFREI_Paris-0D7CC0?logo=data:image/png;base64,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