#include <iostream>
#include <vector>
#include <math.h>
#include <string>
//#include "path.hpp"


//Falta interface observer

class Element{
    protected:
        double coordX, coordY,side, area;
        string color;
    public:
        Element(){};
        Element(double newSide){side=newSide;};
        Element(double newYValue, double newXValue){};
        void setXCoord(double newXValue){coordX=newXValue;};
        void setYCoord(double newYValue){coordY=newYValue;};
        void setSide(double newSide){side=newSide;};
        //void setArea(double newArea){area=newArea;};
        virtual void setArea(){};
        void setColor(string newColor){color=newColor;};
        double getXCoord(){return coordX;};
        double getYCoord(){return coordY;};
        double getSide(){return side;};
        double getArea(){return area;};
        string getColor(){return color;};
};

class Circle:public Element{
    public:
        Circle(){};
        Circle(double newRadio){Element::setSide(newRadio);};
        void setArea(){Element::area= (2 * acos(0.0))*pow(Element::side,2.0);};
        string getString(){return "Circle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Radio = "+to_string(Element::side)+" Area = "+to_string(Element::getArea())+"\n";};

};

class Rectangle:public Element{
    private:
        double width;
    public:
        Rectangle(){};
        void setWidth(double newWidth){width=newWidth;};
        double getWidth(){return width;};
        void setArea(){Element::area= Element::side*width;};
        string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Length = "+to_string(Element::side)+" Width = "+to_string(width)+" Area = "+to_string(Element::getArea())+"\n";};

};

class Ellipse:public Element{
    private:
        double xRadio,yRadio;
    public:
        Ellipse(){};
        void setXRadio(double newXRadio){xRadio=newXRadio;};
        void setYRadio(double newYRadio){yRadio=newYRadio;};
        double getXRadio(){return xRadio;};
        double getYRadio(){return yRadio;};
        void setArea(){Element::area= (2 * acos(0.0))*xRadio*yRadio;};
        string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};

};

class Polyline:public Element{
    private:
        vector<vector<double>> xyCoords;
    public:
        Polyline(){};
        void setXYCoord(vector<double> newxyCoords){xyCoords.push_back(newxyCoords);};
        vector<vector<double>> getXYCoord(){return xyCoords;};
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/

};

class Polygon:public Element{
    private:
        vector<vector<double>> xyCoords;
    public:
        Polygon(){};
        void setXYCoord(vector<double> newxyCoords){xyCoords.push_back(newxyCoords);};
        vector<vector<double>> getXYCoord(){return xyCoords;};
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/

};

class svgDetails{
    protected:
        vector<Element> elementsVector;
        double width, height;
    public:
        svgDetails(){width=0; height=0;};
        void setWidth(double newWidth){width=newWidth;};
        void setHeight(double newHeight){height=newHeight;};
        void setPath(Element newPath){elementsVector.push_back(newPath);};
        double getWidth(){return width;};
        double getHeight(){return height;};

};


