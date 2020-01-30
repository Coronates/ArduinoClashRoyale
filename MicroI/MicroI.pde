import processing.serial.*;

Serial puerto;  

PImage peka1, fondo, rey, soldado, arquera, arquera1, escudo, nube;
int s1=0; int s2=0;
int modoDeJuego=0;
int y1=0; int y2=0; int y3=0;
int y4=0; int y5=0; int y6=0;
int v1=0; int v2=0; int v3=0;
int v4=0; int v5=0; int v6=0;
boolean p1Counted = false; boolean p2Counted = false; boolean p3Counted = false;
boolean p4Counted = false; boolean p5Counted = false; boolean p6Counted = false;
PFont mono;
 
 
 
void setup() {
  // Images must be in the "data" directory to load correctly
  fullScreen();
  peka1 = loadImage("peka1.png", "png");
  rey = loadImage("Rey.png", "png");
  soldado= loadImage("soldado.png", "png");
  fondo = loadImage("fondo.jpg", "jpg");
  arquera = loadImage("arquera.png", "png");
  arquera1 = loadImage("arqueraI.png", "png");
  escudo = loadImage("escudo.png", "png");
  nube = loadImage("muerte.png", "png");
  
  //Lectura de datos del puerto COM 
  puerto = new Serial(this, "COM5", 9600);
  puerto.bufferUntil('\n'); 
  
}


void draw() {
  
  
  String dato = puerto.readStringUntil('\n'); //Lectura de los datos del puerto hasta la siguiente linea
  if(dato != null){
    try{
      int i = dato.indexOf('\n'); //se determinar la posición del último valor de la línea
      String d = dato.substring(0, i-1); //Se formatea la línea quitando el último espaciado
      
      String [] data= d.split(",");  //Se divide la línea en valores separados por comas
      println(d);
      y1= Integer.parseInt(data[0]); //agregar datos a cada variable a utilizar
      y2= Integer.parseInt(data[1]);
      y3= Integer.parseInt(data[2]);
      y4= Integer.parseInt(data[3]);
      y5= Integer.parseInt(data[4]);
      y6= Integer.parseInt(data[5]);
      
      v1= Integer.parseInt(data[6]);
      v2= Integer.parseInt(data[7]);
      v3= Integer.parseInt(data[8]);
      v4= Integer.parseInt(data[9]);
      v5= Integer.parseInt(data[10]);
      v6= Integer.parseInt(data[11]);
      
      modoDeJuego = Integer.parseInt(data[12]);
     
    }catch(Exception e){
      print("error al leer los datos del puerto COM"); //Se captura el error, en caso de que haya uno
    }
    
  }
  
  //Se realizan las acciones para cada modo de juego
  if(modoDeJuego==0){
    //Fondo
  image(fondo, 0, 0);
  
  
   
   pushMatrix(); //Se guarda la configuración actual de coordenadas
   //Arquera1
    translate(0, 0);
    scale(0.08, 0.08); //Redimención de los objetos en la matriz
    fill(0);  
    image(arquera, 3000, 4500);//Inserción de las imagenes
   popMatrix(); //Se reestablecen las coordenadas guardadas
   
      //Arquera2
   pushMatrix();
    translate(0, 0);
    scale(0.08, 0.08);
    fill(0);  
    image(arquera1, 12000, 4500);
   popMatrix();
   
   //Soldado 1
   pushMatrix();
    translate(0, (y1*5)); //translado de los objetos a las posiciones de los soldados
    scale(0.08, 0.08);
    fill(0);  
    image(rey, 4000, 3100);
   popMatrix();

  //Soldado 2
  pushMatrix();
    translate(0, (y2*5));
    scale(0.08, 0.08);
    fill(0);  
    image(soldado, 5200, 3100);
  popMatrix();
  
  //Soldado 3
  pushMatrix();
    translate(0, (y3*5));
    scale(0.08, 0.08);
    fill(0);  
    image(peka1, 6400, 3100);
  popMatrix();
  
   //Soldado 4
  pushMatrix();
    translate(0, (y4*5));
    scale(0.08, 0.08);
    fill(0);  
    image(peka1, 8300, 3100);
  popMatrix();
  
   //Soldado 5
  pushMatrix();
    translate(0, (y5*5));
    scale(0.08, 0.08);
    fill(0);  
    image(soldado, 9500, 3100);
  popMatrix();
  
   //Soldado 6
  pushMatrix();
    translate(0, (y6*5));
    scale(0.08, 0.08);
    fill(0);  
    image(rey, 10700, 3100);
  popMatrix();

  
  //Se resetean las variables usadas en modo de juego 1
  s1 = 0;  s2 = 0;
  p1Counted = false; p2Counted = false; p3Counted = false;
  p4Counted = false; p5Counted = false; p6Counted = false;
  }else if(modoDeJuego==1){
    
  
      if (v1==1){
        
         pushMatrix();
          translate(0, (y1*5));
          scale(0.08, 0.08);
          fill(0);  
          image(nube, 4000, 3100);
         popMatrix();
         //Se verifica si el punto por darle al jugador 1 ya se contó. Si no, se suma 1 punto al total del jugador 1
         if(!p1Counted){
           s1++;
           p1Counted = true;
         }
         
         //s1++;
         //v1=0;
         
      }
      
      if (v2==1){
        
      pushMatrix();
      translate(0, (y2*5));
        scale(0.08, 0.08);
        fill(0);  
        image(nube, 5200, 3100);
        popMatrix();
        if(!p2Counted){
           s1++;
           p2Counted = true;
         }
        //s1++;
        //v2=0;
      }
      
      if (v3==1){
        
      pushMatrix();
        translate(0, (y3*5));
        scale(0.08, 0.08);
        fill(0);  
        image(nube, 6400, 3100);
      popMatrix();
      if(!p3Counted){
           s1++;
           p3Counted = true;
         }
        //s1++;  
        //v3=0;
    }
      
      if (v4==1){
        
      pushMatrix();
        translate(0, (y4*5));
        scale(0.08, 0.08);
        fill(0);  
        image(nube, 8300, 3100);
       popMatrix();
       if(!p4Counted){
           s2++;
           p4Counted = true;
         }
       //s2++;
       //v4=0;
      }
      if (v5==1){
        
       pushMatrix();
        translate(0, (y5*5));
        scale(0.08, 0.08);
        fill(0);  
        image(nube, 9500, 3100);
       popMatrix();
       if(!p5Counted){
           s2++;
           p5Counted = true;
         }
       //s2++;
       //v5=0;
     }
      if (v6==1){
      pushMatrix();
        translate(0, (y6*5));
        scale(0.08, 0.08);
        fill(0);  
        image(nube, 10700, 3100);
      popMatrix();
      if(!p6Counted){
           s2++;
           p6Counted = true;
         }
      //s2++;
      //v6=0;
      }
    
      
      if(s2>=3){
     //Escudo 1
      pushMatrix();
        translate(0, 0);
        scale(0.4, 0.4);
       fill(0);  
       image(escudo, -400,0);
      popMatrix();
      
      pushMatrix();
        stroke(255);
        strokeWeight(10);
        fill(255);
        mono = createFont("fuente.ttf", 50); //adición del tipo de letra 
        textFont(mono);
        text("Victoria!", 250, 180);
      popMatrix();
           
      modoDeJuego=2;
      }
      
      if(s1>=3){
      //Escudo 2
      pushMatrix();
        translate(0, 0);
        scale(0.4, 0.4);
        fill(0);  
        image(escudo, 2000, 0);
      popMatrix();
      
      pushMatrix();
         stroke(255);
         strokeWeight(10);
         fill(255);
         mono = createFont("fuente.ttf", 50);
         textFont(mono);
         text("Victoria!", 700, 180);
      popMatrix();
      modoDeJuego=2;      
      }          
   }
}
