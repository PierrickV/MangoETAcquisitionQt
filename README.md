# MangoETAcquisitionQt
Student's project for [MangoEt](http://www.kikiwi.fr/index.php?page=mango)


TENUM, société créée en 1993, s’est implantée sur le site de Labège Innopole, cœur du tissu industriel et
technologique toulousain. Leur activité se concentre sur le bureau d’études, avec comme atout majeur une
solide expertise dans le domaine des radio-transmissions hors normes.


La carte MangoET est une carte de télémesure qui permet aux utilisateurs de collecter facilement les
résultats d’expériences scientifiques liées à l'étude de l'environnement dans le cadre éducatif. Créé par
Tenum en partenariat avec le Centre National d'Étude Spatiale, Mango entre dans des projets scolaires à
but scientifique.


La conception des capteurs est réalisée par les élèves, aidés de leurs enseignants pour tenter de répondre à
des problématiques environnementales.
La carte est utilisée dans le cadre de projets tel que l’entreprise Argonautica où elle est mise dans une
bouée.


L’extension téléphone (ET) peut être utilisée pour recevoir des informations venant de la carte à distance.
Les anciennes générations de Mango intégraient un module XBee mais ce dernier a été abandonné du fait
de sa courte portée pour être remplacé par le module GSM.
Ainsi la carte MangoET permet d'acquérir des tensions issues de capteurs, de les enregistrer, de les
géolocaliser et de les transmettre par GSM.


Le projet a différents objectifs :


- Essai de capteurs. Dans le cadre de projets scientifiques, des écoliers sont amenés à fabriquer des capteurs
qu'ils devront pouvoir tester via notre application


- Réutilisation du code : Le code source du projet permettra à Tenum de migrer leurs applications vers
l'environnement de développement Qt et les langages de programmation C et C++. Leurs applications sont
actuellement réalisées en Visual Basic (VB).
Le code source devra aussi permettre à des élèves de lycée notamment les étudiants d’IRIS de réaliser leurs
propres applications Mango.


Dans le cadre de notre projet la carte MangoET a deux types d’utilisations :

- Utilisation en direct de la carte sur bureau en guise de carte d’acquisition
La carte est connectée à un ordinateur et permet de faire des mesures en temps réel ou de visualiser des
mesures qui ont été prises ultérieurement. Il est aussi possible d'envoyer des SMS et d'obtenir la position
GPS de la carte.


- Utilisation de la carte « sur le terrain »
Dans le cadre de notre projet, notre application permettra de configurer la fréquence des mesures ainsi que
la fréquence de l'envoi des SMS. Mais elle permettra aussi d’exploiter les résultats des mesures après une
expédition (afficher les mesures des voies enregistrées en expédition et afficher le trajet suivi). Les SMS
sont envoyés à un Smartphone sous Android contenant une application qui permet à l'utilisateur de localiser la carte
