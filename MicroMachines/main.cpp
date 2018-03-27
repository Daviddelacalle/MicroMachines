#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

//caca
#define velocidadMaxima 0.1
#define aceleracion 0.00008
int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");

    //Cargo la imagen donde reside la textura del sprite
     
    sf::Texture tex;
    if (!tex.loadFromFile("resources/micro.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
   sf::Texture map;
     if (!map.loadFromFile("resources/mapa.png"))
    {
        std::cerr << "Error cargando la imagen mapa.png";
        exit(0);
    }
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite(tex);
    sf::Sprite sprite2(map);
    //Le pongo el centroide donde corresponde
    
    sprite.setOrigin(10,10);
    float x=32;
    float y=-460;
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(112, 2, 21, 29));

    
    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(290, 230);
    sprite2.setPosition(32,-460);
    sf::View view1;
    view1.reset(sf::FloatRect(130, 110, 300, 200));
    float angulogirado=0;
    view1.zoom(1.7);
    float angulo=270;
    float velocidad=0;
    int tipoDeceleracion=0;
    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {

                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }

            }
            
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                tipoDeceleracion=1;
                if(velocidad<velocidadMaxima){
                    velocidad=velocidad+aceleracion;
                }
                sprite.move(cos((angulo)*3.1419/180)*velocidad,sin((angulo)*3.1419/180)*velocidad);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                tipoDeceleracion=2;
                if(velocidad>-velocidadMaxima){
                    velocidad=velocidad-aceleracion;
                }
                sprite.move(cos((angulo)*3.1419/180)*(velocidad),sin((angulo)*3.1419/180)*(velocidad));
            }
        }
        else{
            if(velocidad!=0){
                if(tipoDeceleracion==1){
                    velocidad=velocidad-aceleracion;
                    sprite.move(cos((angulo)*3.1419/180)*(velocidad),sin((angulo)*3.1419/180)*(velocidad));
                    if(velocidad<0){
                        velocidad = 0;
                    }
                }
                if(tipoDeceleracion==2){
                    velocidad=velocidad+aceleracion;
                    sprite.move(cos((angulo)*3.1419/180)*(velocidad),sin((angulo)*3.1419/180)*(velocidad));
                    if(velocidad>0){
                        velocidad = 0;
                    }
                }
            }
        }
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && velocidad!=0) {            
            angulo=angulo+0.05;
            if(velocidad!=0){
                sprite.setRotation(angulogirado); 
                angulogirado=angulogirado+0.05;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && velocidad!=0) {
                angulo=angulo-0.05; 
                if(velocidad!=0){
                    sprite.setRotation(angulogirado);
                    angulogirado=angulogirado-0.05;
                }
        }
         std::cout << velocidad << std::endl;
        
        
        
        view1.setCenter(sprite.getPosition());
        window.clear();
        window.setView(view1);
        window.draw(sprite2);
        window.draw(sprite);
        window.display();
    }

    return 0;
}