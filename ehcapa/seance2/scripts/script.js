/*
  Les blocs de commentaires javascript
  s'écrivent ainsi. 
*/
// les commentaires sur une seule ligne se font ainsi.


/*
  Fichier de script type.
  On y trouve une fonction d'initialisation (init) déclenchée à la fin du chargement du document html.
  Le lien entre l'événement décrivant la fin du chargement et l'appel à la fonction d'initialisation se fait dans le bloc "BLOC A"
*/

// Déclaration de variables "constantes" par le mot clef "const". 
// Les variables "variables" sont introduites par le mot clef "let".
// Attention, on voit encore utilisé le mot clef "var". (écriture antérieure à 2016).
// Ces variables étant déclarée en dehors de tout bloc, elle est considérée comme globale.
// Dans la mesure du possible, on limitera les variables globales 
// 
// Les déclarations sont accompagnées d'une affectation (signe égal simple) pour former une instruction (ou "statment") 
// fermé par un ";" (optionnel mais plus propre).
// 
// Notez que les variables ne sont pas typées (typage lâche). Une variable peut changer de type. 
// Le langage Typescript, une surcouche de JS, permet de réguler ce changement de type.   
const _HTML_info = "<p>Voici un liste mise à jour dynamiquement par javascript. <br> \
  Apprès avoir appuyé sur le boutton 'Démarrer', cliquez quelque part sur la page pour y ajouter un élément.</p>";
const _Text_prompt = "Quel est le contenu du nouvel élément de la liste?";
const _Text_updatePrompt = "Quel est le nouveau contenu de cet élément de liste?";
let _Bool_listening = false; // On passera cette variable à true quand l'utilisateur appuiera sur le boutton "Démarrer".
const _Text_btn_start = "Démarrer";
const _Text_btn_stop = "Arrêter";
const _Text_btn_suppr = "supression";


//-------------- BLOC A
// le bloc suivant permet de s'asurer que l'ensemble du document html 
// a été chargé dans l'objet JS global "document" avant de manipuler celui-ci 
window.addEventListener("DOMContentLoaded", init);
// Il ajoute un écouteur d'événement (la fonciton de rappel "init") à l'objet global "window". 
// L'événement attendu est "DOMContentLoaded". 
//    C'est un évenement lancé par le moteur JS indiquant que l'objet "Document Object Model" (DOM) 
//    est complet et qu'il est manipulable.
// L'objet "window" représente donc une fenêtre contenant un document DOM et 
//    la propriété "document" pointe vers le document DOM chargé dans cette fenêtre. 
// !!!!!!!!!!!!!!!!!!
// Ce bloc doit être présent dans vos fichiers de scripts accédant le DOM afin d'éviter de manipuler un élément qui n'est pas encore chargé (image, ..).
// !!!!!!!!!!!!!!!!!!
//--------------

// Déclaration de la fonction init
// La fonction étant appelée à la survenue d'un évenement, il s'agit d'une "callback" (fonction de rappel). 
function init(){

  // Déclaration et affectation de variables locales à la fonction.
  //
  // La variable (html) va contenir l'objet JS correspondant à l'élément <html> 
  // La méthode querySelector() de "document" retourne le premier élement dans le document correspondant au sélecteur (ici "html")..  
  const html = document.querySelector('html');
  // la méthode getElementById() de "document" renvoie un objet Element représentant l'élément dont 
  // la propriété id correspond à la chaîne de caractères spécifiée.
  const div_GUI = document.getElementById("GUI");

  //
  // La  variable (list) contient un objet JS correspondant à un élément <ul> créé pour l'occasion grâce à la méthode "createElement"
  // Attention, cet élément n'est pas encore rattaché à l'arborescence du DOM.  
  const list = document.createElement('ul');
  const info = document.createElement('p');
  const btn_start = document.createElement('button');
  
  // Affectation d'une valeur à la propriété "textContent" de l'élément "info".et "btn_start"
  info.innerHTML = _HTML_info;
  btn_start.innerHTML = _Text_btn_start;


  // On rattache les éléments "info", "list" et "btn_start" à l'élément "div_GUI" du DOM. 
  div_GUI.appendChild(info);
  div_GUI.appendChild(list);
  div_GUI.appendChild(btn_start);


  // Notez que gestionnaire d'événement utilise une fonction anonyme, déclarée comme paramètre de la fonction addEventListener
  btn_start.addEventListener(
    "click",
    // Ici, on va mettre en place un mécanisme de basculement start/stop sur le bouton. 
    function(theEvent){ // la variable TheEvent va être initialisée avec l'événement déclencheur (click sur le boutton)
      theEvent.stopPropagation();// Cette instruction évite que l'événement soit aussi récupéré par le deuxième eventListener. 
      // Ci-dessous : remarquez l'usage du triple égal (égalité stricte)
      // L'opérateur d'égalité stricte (===) vérifie si ses deux opérandes sont égaux et renvoie un booléen correspondant au résultat. 
      // À la différence de l'opérateur d'égalité, l'opérateur d'égalité stricte considère toujours des opérandes de types différents comme étant différents
      if(true === _Bool_listening){ // On aurait pu faire un simple if(_Bool_listening).
        _Bool_listening = false;
        btn_start.innerText = _Text_btn_start;
      }else{
        _Bool_listening = true;
        btn_start.innerText = _Text_btn_stop;
      }
    }
  )

  // Ajout d'un écouteur d'événement sur l'objet "html"
  // l'événement attendu est "click" et il doit survenir sur l'objet "html".
  // Le comportement est donc le suivant : dès que l'utilisateur click n'importe où sur la page, la callback est appelée.
  // ici, la callback est une fonction anonyme 
  html.addEventListener(
    "click", 
    function() {
      if(_Bool_listening){
        listItem = document.createElement('li');
        // l'appel à la fonction globale "prompt" déclenche l'ouverture d'une modale munie d'un champs texte à remplir par l'utilisateur.
        // La valeur rentrée par l'utilisateur sera retournée par la fonction.
        const listContent = prompt(_Text_prompt);

        btn_listItem = document.createElement('button');
        btn_listItem.innerHTML = _Text_btn_suppr;

        
        btn_listItem.addEventListener(
          "click",
          function(enRoute){
            enRoute.stopPropagation();
            list.removeChild(this.parentElement);
          }
        )

        listItem.innerText = listContent;
        listItem.appendChild(btn_listItem);

        listItem.addEventListener(
          "click",
          function(e) {
            if(_Bool_listening){
              // la variable e contient l'événement déclencheur de la callback
              // stopPropagation évite que l'événement click sur l'élément de liste ne soit aussi intercpté par l'élément html.
              // Ainsi, une seule callback sera appelée.
              e.stopPropagation();
              const listContent = prompt(_Text_updatePrompt);
              this.textContent = listContent;
            }
          }
        );


        list.appendChild(listItem);
      }
    }
  );

  
}

