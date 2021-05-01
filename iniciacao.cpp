#include "ringue.h"
#include "iniciacao.h"
#include "tinyxml/tinyxml.h"

#include <math.h>



void Iniciacao::CalculaCoeficienteCabecas(){

    GLfloat deltaX = abs(gXLutador - gXBot);
    GLfloat deltaY = abs(gYLutador - gYBot);

    GLfloat tangente = deltaX/deltaY;
    GLfloat angulo = (atan (tangente) * 180 / 3.14);

    gGiroBot = angulo;
    gGiroLutador = angulo;

    //Bot
    if(gYBot > gYLutador && gXLutador > gXBot)
    {
        gGiroBot = 180 + gGiroBot;
    }
    
    else if(gYBot > gYLutador && gXBot > gXLutador)
    {
        gGiroBot = 90 + gGiroBot;
        gGiroLutador = 360 - gGiroLutador;
    }
    
    else if(gXBot == gXLutador && gYBot > gYLutador)
    {
        gGiroBot = 180 + gGiroBot;
    }
    
    else if(gYLutador > gYBot && gXLutador > gXBot)
    {
        gGiroBot = 360 - gGiroBot;
    }
    
    else if(gYLutador ==  gYBot && gXLutador > gXBot)
    {
        gGiroBot = 180 + gGiroBot;
    }

    // Lutador
    if(gYLutador > gYBot && gXBot > gXLutador)
    {
        gGiroLutador = 180 + gGiroLutador;
    }
    
    else if(gYLutador > gYBot && gXLutador > gXBot)
    {
        gGiroLutador = 90 + gGiroLutador;
        gGiroBot = 360 - gGiroBot;
    }
    
    else if(gXLutador == gXBot && gYLutador > gYBot)
    {
        gGiroLutador = 180 + gGiroLutador;
    }
    
    else if(gYBot > gYLutador && gXBot > gXLutador)
    {
        gGiroLutador = 360 - gGiroLutador;
    }
    
    else if(gYBot == gYLutador && gXBot > gXLutador)
    {
        gGiroLutador = 180 + gGiroLutador;
    }

}

void Iniciacao::TipoJogo(bool &modoTreino)
{
    string tipoJogo;
    cout << "Modo treino? (T). Ou digita qualquer outra coisa para jogar com o bot perseguidor. " << endl;
    cin >> tipoJogo; 

    if(tipoJogo == "T" || tipoJogo == "t")
    {
        modoTreino = true;
    }
    else
    {
        modoTreino = false;
    }

} 

string Iniciacao::ObtemNomeArquivo()
{
    string nomeArquivo;
    cout << "Insere o caminho do arquivo SVG aí fera: ";
    cin >> nomeArquivo; 

    // Só dando uma limpadinha né
    cout << flush; 
    return nomeArquivo;
}

void Iniciacao::ProcessaArena(TiXmlElement *arena)
{
    width = atoi(arena->Attribute("width"));
    height = atoi(arena->Attribute("height"));    

    xArena = atoi(arena->Attribute("x"));
    yArena = atoi(arena->Attribute("y"));

    widthHalf = width/2;
    heightHalf = height/2;

}

void Iniciacao::ProcessaLutadores(TiXmlElement *lutador1, TiXmlElement *lutador2)
{    
    if(strcmp (lutador1->Attribute("fill"),"red") == 0)
    {
        gXLutador = (atoi(lutador2->Attribute("cx")) - xArena ) - widthHalf;
        gYLutador = - (atoi(lutador2->Attribute("cy")) - yArena )+ heightHalf;
        rCabecaLutador = atoi(lutador2->Attribute("r"));

        
        gXBot = (atoi(lutador1->Attribute("cx")) - xArena ) - widthHalf;
        gYBot = - (atoi(lutador1->Attribute("cy"))- yArena ) + heightHalf;
        rCabecaBot = atoi(lutador1->Attribute("r"));
    }
    else if(strcmp (lutador2->Attribute("fill"),"red") == 0)
    {
        gXLutador = (atoi(lutador1->Attribute("cx")) - xArena ) - widthHalf;
        gYLutador = - (atoi(lutador1->Attribute("cy"))- yArena ) + heightHalf;
        rCabecaLutador = atoi(lutador1->Attribute("r"));

        gXBot = (atoi(lutador2->Attribute("cx")) - xArena ) - widthHalf;
        gYBot = - (atoi(lutador2->Attribute("cy"))- yArena ) + heightHalf;
        rCabecaBot = atoi(lutador2->Attribute("r"));
    } 

    CalculaCoeficienteCabecas();       
}

void Iniciacao::IniciaLutadores(Lutador &lutador, Lutador &bot)
{    
    // gXLutador = (ladoRingue * gXLutador)/width;
    // gYLutador = (ladoRingue * gYLutador)/width;

    // gXBot = (ladoRingue * gXBot)/width;
    // gYBot = (ladoRingue * gYBot)/width;
    lutador.Iniciacao(gXLutador, gYLutador, 0, gGiroLutador, rCabecaLutador, false);

 //   lutador.Iniciacao(0,0, 0, gGiroLutador, rCabecaLutador, false);
    bot.Iniciacao(gXBot, gYBot, 0, gGiroBot, rCabecaBot, true);
}

void Iniciacao::IniciaArena(GLint &widthArena, GLint &heightArena, GLint &widthHalfArena, GLint &heightHalfarena, Ringue &ringue)
{
    widthArena = width;
    heightArena = height;

    widthHalfArena = widthHalf;
    heightHalfarena = heightHalf;

    ringue.Iniciacao(widthArena, heightArena);

}
bool Iniciacao::ProcessaArquivo(char* nomeArquivo)
{
    // /home/leticia/Documents/arena_3.svg


    // Passando de string pra char array pq se não dá ruim
    // int n = nomeArquivo.length(); 
    // char char_array[n + 1]; 
    // strcpy(char_array, nomeArquivo.c_str());

    // Abrindo o arquivo
    TiXmlDocument doc(nomeArquivo);

    TiXmlElement *svg; 
    TiXmlElement *rect;
    TiXmlElement *circle1; 
    TiXmlElement *circle2; 


	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
        svg = doc.FirstChildElement("svg");
        if(svg)
        {
            rect = svg->FirstChildElement("rect");
            if(rect)
            {
                ProcessaArena(rect);
            }

            circle1 = svg->FirstChildElement("circle");
            circle2 = circle1->NextSiblingElement("circle");

            if(circle1 && circle2)
            {
                ProcessaLutadores(circle1, circle2);
            }
            cout << "Deu bom abrindo o arquivo!" << endl;

        }
        return true;
	}
	else
	{
        cout << "Vish, deu ruim abrindo esse SVG D: \n" << endl;
        return false;
	}

}