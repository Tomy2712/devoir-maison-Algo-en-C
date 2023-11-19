#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct noeud {
    char categorie;
    int valeur;
    struct noeud *gauche;
    struct noeud *droit;
} noeud;

typedef noeud *expression;

expression variable() {
    expression exp = malloc(sizeof(noeud));
    exp->categorie= 'v';
    exp->valeur = 'x';
    exp->gauche = NULL;
    exp->droit = NULL;
    return exp;
}

expression coefficient(int valeur) {
    expression exp = malloc(sizeof(noeud));
    exp->categorie= 'c';
    exp->valeur= valeur;
    exp->gauche = NULL;
    exp->droit = NULL;
    return exp;
}

expression op_binaire(char c, expression exp1, expression exp2) {
    expression exp = malloc(sizeof(noeud));
    exp->categorie= 'b';
    exp->valeur = c;
    exp->gauche = exp1;
    exp->droit = exp2;
    return exp;
}

expression op_unaire(char c, expression exp1) {
    expression exp = malloc(sizeof(noeud));
    exp->categorie = 'u';
    exp->valeur = c;
    exp->gauche = exp1;
    exp->droit = NULL;
    return exp;
}

expression copie_expression(expression exp) {
    if(exp == NULL)
        return NULL;
    expression exp_c = malloc(sizeof(noeud));
    exp_c->categorie = exp->categorie;
    exp_c->valeur = exp->valeur;
    exp_c->gauche = copie_expression(exp->gauche);
    exp_c->droit = copie_expression(exp->droit);

    return exp_c;
}

void affiche_terme(expression exp, bool premier) {
    bool pd = false;
    if(exp == NULL)
        return;
    if(!premier && (exp->gauche != NULL || exp->droit != NULL)) {
        printf("(");
        pd = true;
    }

    affiche_terme(exp->gauche, false);
    if(exp->categorie=='c')
        printf("%d", exp->valeur);
    else
        printf("%c", exp->valeur);

    affiche_terme(exp->droit, false);

    if(pd)
        printf(")");
}

void affiche_expression(expression exp) {
    affiche_terme(exp, true);
}

// TODO --> verif sir sous enfant gauche droite (en fonction de bin ou non) --> faire calcul & remonter resultat 
//          si solo juste pow / racine 
//          obliger de faire 50 cases avec - + * / etc...

char* evaluate_expression(expression exp, float valeurDeX) {
    if(exp == NULL) 
        return 0;
    char* gauche = evaluate_expression(exp->gauche, valeurDeX);
    char* droit = evaluate_expression(exp->droit, valeurDeX);
    if(exp->categorie == 'b' || exp->categorie == 'c') {
        return "-_-";
    } 
}

void free_expression(expression exp) {
    if(exp == NULL)
        return;
    free_expression(exp->gauche);
    free_expression(exp->droit);
    free(exp);
}

int main(int argc, char** argv) {
    expression e0 = op_binaire('*', coefficient(5), variable());
    printf("Expression e0 : ");
    affiche_expression(e0);
    free_expression(e0);
    printf("\n");
    expression e1 = op_binaire('*', op_binaire('+', op_binaire('*', coefficient(3), variable()), coefficient(1)), op_binaire('+', variable(), coefficient(2)));
    printf("Expression e1 : ");
    affiche_expression(e1);
    free_expression(e1);
    printf("\nModif : ");
    evaluate_expression(e1,2.2);
    printf("erujygoeurg\n");
    //affiche_expression(e1);
    //free_expression(e1);
    return EXIT_SUCCESS;
}