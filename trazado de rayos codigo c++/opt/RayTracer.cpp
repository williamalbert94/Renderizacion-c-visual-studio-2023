#include "RayTracer.h"
#include <typeinfo>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <random>

using namespace std;
#define EPS 1E-2

rayTracer::rayTracer(escena* s, int sm,int depth){
  Escena = s;
  muestras = sm;
  maxdepth = depth;
}

objeto * rayTracer::intersecta(rayo r){
  Escena->inicializacion();
  objeto * current = NULL;
  objeto * minObject = NULL;
  Point inter;

  Point min = Point::Infinite();
  while((current = Escena->retorna_objetos()) != NULL){
    inter = current->retornainterseccion(r);
    if((inter - r.p).length() > 1E-6){
      if((inter-r.p).length()  < (min-r.p).length()){
        min = inter;
        minObject = current;
      }
    }
  }
  return minObject;
}


Color rayTracer::Trazarayo(rayo r, int depth){
  Color c_=Color(0.0,0.0,0.0,0.0);

  if (depth > this->maxdepth)
  {
      return c_; //End recurssion
  }

  objeto* hit = intersecta(r);
  if (hit != NULL) {
      Point hit_light = hit->retornainterseccion(r);
      if (hit_light.x==0 && hit_light.y==0 && hit_light.z==0) {
          c_ = c_;
      }
      else {
          Material* mat = hit->retornamaterial();
          c_ = EvalPhong(hit->retornanormal(hit_light), hit_light, r, mat, hit);
          hit->retornamaterial();
      }
      Material* material = hit->retornamaterial();

      if (material->type == REFLECTIVO)
      {
          depth += 1;

          rayo reflectedRay = r.reflexion(hit->retornanormal(hit_light), hit_light);
          reflectedRay.p = reflectedRay.p + (reflectedRay.v * EPS); // Move along a smidge

          c_ = c_ + rayTracer::Trazarayo(reflectedRay, depth);
      }
  }
  return c_;
}

////
//summario
///


Color rayTracer::EvalPhong(Point normal, Point p, rayo r, Material * m, objeto * o)
{
    Color ret = Color(0.0, 0.0, 0.0, 1.0);
    normal.normalize();
    // YOUR CODE HERE.
    // There is ambient lighting irrespective of shadow.
    // For each Light Source L do:
    // Point pointLight =  scene->getNextLight();
    vector <Point> pointLights = Escena->luces;


    Color LightColor = Color(1.0, 1.0, 1.0, 1.0); // White light
    //LightColor = LightColor + LightColor;
    double LightPower = 1.0; // Should be based on distance to light maybe?

    // Everything get hits by ambient light
    Color ambientColor = m->retornaambiente(p) * LightPower*0.25;

    Color diffuse = Color(0.0, 0.0, 0.0, 1.0);
    Color specularHighlight = Color(0.0, 0.0, 0.0, 1.0);

    for (int i = 0; i < pointLights.size(); i++)
    {
        // If L visable
        // Draw ray from light to object, end if blocked by an object

        // Find Direction towards light
        Point lightDirection = (pointLights[i] - p);
        lightDirection.normalize();

        rayo lightRay(p + lightDirection * EPS, lightDirection); // Ray from light to Object. Point in direction of light and make sure it hits a light


        objeto* hitObj = intersecta(lightRay);

        double reflectiveness = 1000.0 * m->kr;

        // Check if in shadow
        // Object should be in the way of the light

        if (hitObj == NULL || (normal * lightDirection < 0))
        {
            // Add Difuse component
            Color diffuseColor = m->retornadifuso(p);
            // ret = ret + diffuseColor;

            // // Add specular component
            Color specularColor = m->retornaespecular(p);
            // ret = ret + specularColor;

            //double distance = (pointLights[i] - p).length;

            // Calc Diffuse 

            double lDotNormal = normal * lightDirection;

            lDotNormal = lDotNormal < 0 ? 0.0f : lDotNormal; // Makes sure angle > 0

            diffuse = diffuse + (diffuseColor * LightPower * lDotNormal);

            diffuse = diffuse + (diffuseColor * LightPower * m->kd * lDotNormal);

            // Calc Specular
            // SPECULAR
            Point toCamera = r.v * -1;
            toCamera.normalize();

            Point disFromLight = toCamera + lightDirection;
            disFromLight.normalize();   // divide by length
            double specReflec = disFromLight * normal;
            specReflec = specReflec < 0 ? 0.0f : specReflec; // Makes sure angle > 0

            double refectivity = pow(specReflec, reflectiveness);

            specularHighlight = specularHighlight + specularColor * LightPower * refectivity;
        }

        //else // In shadow, some object blocks light 
        {
            // cout << "\n Lightx: " << pointLights[i].x << endl;
            // cout << "\n Lighty: " << pointLights[i].y << endl;

            // Calculate Radance, rad at point
            // rad = rad + Radiance at point
            // Code taken from Assignment 3 shader

            //ret = ret + pointLights[i]
            // Something blocking light path

        }


    }


    // if (typeid(*o) == typeid(Triangle) )
    //   ret = Color(0.1,1.0,0.0,0.0);
    // else
    //   ret = Color(0.1,1.0,1.0,0.0);

    Color finalColor = ambientColor+diffuse + specularHighlight; // Add all components of light together

    return finalColor;

  //  Color ret = Color(0.0, 0.0, 0.0, 1.0);
  //  normal.normalize();
  //  vector <Point> pointLights = Escena->luces;


  //  Color LightColor = Color(1.0, 1.0, 1.0, 1.0); // White light

  //  double LightPower = 1.0; 

  //  double atenuacion = 0.3;

  //  Color ambientColor = m->retornaambiente(p) * LightPower *atenuacion;

  //  Color diffuse = Color(0.0, 0.0, 0.0, 1.0);
  //  Color specularHighlight = Color(0.0, 0.0, 0.0, 1.0);

  //  for (int i = 0; i < pointLights.size(); i++)
  //  {

  //      Point lightDirection = (pointLights[i] - p);
  //      lightDirection.normalize();

  //      rayo lightrayo(p + lightDirection * EPS, lightDirection); 


  //      objeto* hitObj = intersecta(lightrayo);

  //      double reflectiveness = 1000.0 * m->kr;

 

  //      if (hitObj == NULL || (normal * lightDirection < 0))
  //      {

  //          Color diffuseColor = m->retornadifuso(p);



  //          Color specularColor = m->retornaespecular(p);



  //          double lDotNormal = normal * lightDirection;

  //          lDotNormal = lDotNormal < 0 ? 0.0f : lDotNormal; 

  //          diffuse = diffuse + (diffuseColor * LightPower * lDotNormal);

  //          diffuse = diffuse + (diffuseColor * LightPower * m->kd * lDotNormal);


  //          Point toCamera = r.v * -1;
  //          toCamera.normalize();

  //          Point disFromLight = toCamera + lightDirection;
  //          disFromLight.normalize();   // divide by length
  //          double specReflec = disFromLight * normal;
  //          specReflec = specReflec < 0 ? 0.0f : specReflec;

  //          double refectivity = pow(specReflec, reflectiveness);

  //          specularHighlight = specularHighlight + specularColor * LightPower * refectivity;
  //      }




  //  }

  //  Color finalColor = diffuse ; // Add all components of light together


  //return finalColor;
}



///////////////////////////////////
// #summary
// funcion de renderizacion
///////////////////////////////////







Color rayTracer::renderiza(int x, int y){
  Color c = Color(0.0,0.0,0.0,0.0);
  for (int i = 1; i <= muestras; i++) {

      for (int j = 1; j <= muestras; j++) {
          double one, two;
          //origen es 0.5
          one = double(x) - 0.5 + double(i) / double(muestras);
          two = double(y) - 0.5 + double(j) / double(muestras);
          rayo r = Escena->generarayo(one, two);
          c = c + Trazarayo(r, 0);
      }
  }
  c = c*(1/double(muestras * muestras));
  return c;
}

