
// Signe du joueur
function signe_joueur(round) {
    if ((round % 2) == 0)
    {
        return 'X';
    }
    else
    {
        return 'O';
    }
}

// Modifier le joueur
function modif_player(round) {
    let para = document.querySelector('p');
    para.innerHTML = 'Player ' + ((round % 2) + 1);
}

// Si case pleine
function pleine(choix) {
    // Reset alerte
    let resultat = document.querySelector('#result');
    resultat.innerHTML = '';

    //Contenu
    let val = choix.innerHTML;
    
    //Check
    if (val == 'X' || val == 'O')
    {
        resultat.innerHTML = 'Cette case est deja remplie !';
        return true;
    }
    return false;
}

// Gagnant
function win(player)
{
    let cases = document.querySelectorAll("td");
    
    //Ligne
    for (let i = 0 ; i < cases.length ; i = i + 3)
    {
        // Ligne
        let x1 = cases[i].innerHTML;
        let x2 = cases[i+1].innerHTML;
        let x3 = cases[i+2].innerHTML;

        if (x1 == x2 && x2 == x3 && x3 !== '')
        {
            return player;
        }
    }

    //Collones
    for (let i = 0 ; i < 3 ; i++)
    {
        // Ligne
        let x1 = cases[i].innerHTML;
        let x2 = cases[i+3].innerHTML;
        let x3 = cases[i+6].innerHTML;

        if (x1 == x2 && x2 == x3 && x3 !== '')
        {
            return player;
        }
    }

    //Diagonale
    if ((cases[0].innerHTML == cases[4].innerHTML && cases[4].innerHTML == cases[8].innerHTML
        || cases[6].innerHTML == cases[4].innerHTML && cases[4].innerHTML == cases[2].innerHTML)
        && cases[4].innerHTML !== "")
    {
        return player;
    }
    return -1;

}

//Fin de jeu
function end(round) {
    let winner = win(round % 2);

    if (winner !== -1)
    {
        document.querySelector('#player').remove();
        document.querySelector('#result').innerHTML = "Player " + (winner+1) + " wins !";
        return 9;
    }
    else if (round == 8)
    {
        document.querySelector('#player').remove();
        document.querySelector('#result').innerHTML = "It's a draw !";
        return 9;
    }
    else
    {
        // Prochain round
        round++;

        //Modifier le joueur
        modif_player(round);

        //Return
        return round;
    }
}

// Jeu
function jeu(choix, round) {
    if (pleine(choix) == false)
    {
        //Signe du joueur
        signe = signe_joueur(round);

        //Modifier case
        choix.innerHTML = signe;

        //Fin
        round = end(round);
    }

    // Fin
    return round;
}

// Start
let round = 0;
document.addEventListener('DOMContentLoaded', function() {
    // Les cases
    let cases = document.querySelectorAll("td");

    //Pour chaque case
    cases.forEach(choix => {
        choix.addEventListener('click', function() {
            if (round < 9)
            {
                round = jeu(choix, round);
            }
        });
    })
});