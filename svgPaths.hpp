/*class Plataforma : public Subject {
private:
    list<Observer*> estudiantes;

public:
    Plataforma() {}
    ~Plataforma() {}

    void attach(Observer* est) {
        estudiantes.emplace_back(est);
    }

    void detach(Observer* est) {
        estudiantes.remove(est);
    }

    void notify(void* curso) {
        for (Observer* actual : estudiantes) {
            thread t(&Observer::update, actual, curso); // parametros = (direccionDeMetodo, instancia/objeto, parametro)
            t.join(); // espere a que t termine
        }
    }
};*/

#include <math.h>

class Element{
    protected:
        double coordX, coordY,side, area, finalCoordX, finalCoordY, hypotenuse, displacement;
        bool rect;
        vector<vector<int>> movements; // { {x,y}, {}, {}, {} }
        string color, attribute;
    public:
        Element(){};
        Element(double newSide){side=newSide;};
        Element(double newYValue, double newXValue){};
        void setXCoord(double newXValue){coordX=newXValue;};
        void setYCoord(double newYValue){coordY=newYValue;};
        void setFinalXCoord(double pNewfinalCoordX){finalCoordX = pNewfinalCoordX;};
        void setFinalYCoord(double pNewfinalCoordY){finalCoordY = pNewfinalCoordY;};
        void setHypotenuse(double pNewHypotenuse){hypotenuse = pNewHypotenuse;};
        void setDisplacement(double pNewDisplacement){displacement = pNewDisplacement;};
        void setSide(double newSide){side=newSide;};
        void setRect(bool newRect){rect = newRect;};
        //void setArea(double newArea){area=newArea;};
        //virtual void setArea(){};
        virtual void findMatchPosition(){};
        void setColor(string newColor){color=newColor;};
        double getXCoord(){return coordX;};
        double getYCoord(){return coordY;};
        double getSide(){return side;};
        double getArea(){return area;};
        string getColor(){return color;};
        double getDisplacement(){return displacement;};
        double getFinalXCoord(){return finalCoordX;};
        double getFinalYCoord(){return finalCoordY;};
        double getHypotenuse(){return hypotenuse;};
        string getAttribute(){return attribute;};
        vector<vector<int>> getMovements(){return movements;};
        bool isRect(){return rect;};
        void addMovement(int x, int y){
            vector<int> point = {x,y}; movements.push_back(point);
        };

        virtual void createSVGAttribute(xml_document<> *myDoc){};
};

class Circle:public Element{
    private:
    public:
        Circle(){Element::attribute = "circle";};
        Circle(double newRadio, double newXCoord, double newYCoord, string newColor){Element::setXCoord(newXCoord);Element::setYCoord(newYCoord);
        Element::setSide(newRadio);Element::setColor(newColor);Element::attribute = "circle";};
        Circle(double newRadio){Element::setSide(newRadio);};
        void setArea(){Element::area= (2 * acos(0.0))*pow(Element::side,2.0);};
        bool findMatchPosition(double pXValue, double pYValue);
        string getString(){return "Circle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Radio = "+to_string(Element::side)+" Area = "+to_string(Element::getArea())+"\n";};

        void createSVGAttribute(xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            myDoc->first_node()->append_node(newNode);
            xml_attribute<> *cx = myDoc->allocate_attribute("cx", to_string(coordX).c_str());
            newNode->append_attribute(cx);
            xml_attribute<> *cy = myDoc->allocate_attribute("cy", to_string(coordY).c_str());
            newNode->append_attribute(cy);
            xml_attribute<> *r = myDoc->allocate_attribute("r", to_string(side).c_str());
            newNode->append_attribute(r);
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", color.c_str());
            newNode->append_attribute(fill);
        }

};

 bool Circle::findMatchPosition(double pXValue,double pYValue){

    if(pow((pXValue-(Element::coordX)),2.0)+pow((pYValue-(Element::coordY)),2.0)<=pow(Element::getSide(),2.0)){
        cout<<"\npertenece\n";
        return true;
     }
     else{
        cout<<"\nNO PERTENECE\n";
        return false;
     }
}


class Rectangle:public Element{
    private:
        int width, height;
    public:
        Rectangle(){Element::attribute = "rect";};
        Rectangle(double newWidth){width=newWidth;};
        Rectangle(double newWidth, double newXCoord, double newYCoord, string newColor, double newHeight){width=newWidth;Element::setXCoord(newXCoord);
        Element::setYCoord(newYCoord);Element::setSide(newHeight);Element::setColor(newColor); Element::attribute = "rect";};
        void setWidth(double newWidth){width=newWidth;};
        void setHeight(double newHeight){height=newHeight;};
        int getWidth(){return width;};
        int getHeight(){return height;};
        bool findMatchPosition(double pXValue, double pYValue);
        /*void setArea(){Element::area= Element::side*width;};
        string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Length = "+to_string(Element::side)+" Width = "+to_string(width)+" Area = "+to_string(Element::getArea())+"\n";};*/
        
        void createSVGAttribute(xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            myDoc->first_node()->append_node(newNode);
            xml_attribute<> *x = myDoc->allocate_attribute("x", to_string(coordX).c_str());
            newNode->append_attribute(x);
            xml_attribute<> *y = myDoc->allocate_attribute("y", to_string(coordY).c_str());
            newNode->append_attribute(y);
            xml_attribute<> *attrWidth = myDoc->allocate_attribute("width", to_string(width).c_str());
            newNode->append_attribute(attrWidth);
            xml_attribute<> *attrHeight = myDoc->allocate_attribute("height", to_string(height).c_str());
            newNode->append_attribute(attrHeight);
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", color.c_str());
            newNode->append_attribute(fill);
        }

};

bool Rectangle::findMatchPosition(double pXValue, double pYValue){
    double maxWidth=Element::getXCoord()+width, maxLength=Element::getYCoord()+Element::getSide();
    //cout<<pXValue<<" "<<pYValue;
    if((pXValue<=maxWidth&&(pXValue>=Element::getXCoord()))&&(pYValue<=maxLength&&(pYValue>=Element::getYCoord()))){
        cout<<"\nDENTRO\n";
        return true;
    }
    else{
        cout<<"\nAFUERA\n";
        return false;
    }

/*
    if((pXValue<maxWidth)&&(pXValue>Element::getXCoord())&&(pYValue==Element::getYCoord())){
        cout<<"Borde Superior";
    }
    if((pXValue<=maxWidth)&&(pXValue>=Element::getXCoord())&&(pYValue==minLength)){
        cout<<"Borde Inferior";
    }
    if((pXValue==maxWidth)&&((pYValue>=minLength)&&(pYValue<=Element::getYCoord()))){
        cout<<"Borde Derecha";
    }
    if((pXValue==Element::getXCoord())&&((pYValue>=minLength)&&(pYValue<=Element::getYCoord()))){
        cout<<"Borde izquierda";
    }*/


}

class Ellipse:public Element{
    private:
        double yRadio;
    public:
        Ellipse(){Element::attribute = "ellipse";};//FALTA CAMBIAR LOS XRADIO POR SETSIDE
        Ellipse(double newXRadio,double newYRadio, double newXCoord, double newYCoord, string newColor){Element::setSide(newXRadio);yRadio=newYRadio;
        Element::setColor(newColor);Element::setXCoord(newXCoord);Element::setYCoord(newYCoord); Element::attribute = "ellipse";};
        void setXRadio(double newXRadio){Element::setSide(newXRadio);};
        void setYRadio(double newYRadio){yRadio=newYRadio;};
        double getXRadio(){return Element::getSide();};
        double getYRadio(){return yRadio;};
        bool findMatchPosition(double pXValue, double pYValue);
       /* void setArea(){Element::area= (2 * acos(0.0))*xRadio*yRadio;};
        string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/
        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            myDoc->first_node()->append_node(newNode);
            xml_attribute<> *cx = myDoc->allocate_attribute("cx", to_string(coordX).c_str());
            newNode->append_attribute(cx);
            xml_attribute<> *cy = myDoc->allocate_attribute("cy", to_string(coordY).c_str());
            newNode->append_attribute(cy);
            xml_attribute<> *rx = myDoc->allocate_attribute("rx", to_string(side).c_str());
            newNode->append_attribute(rx);
            xml_attribute<> *ry = myDoc->allocate_attribute("ry", to_string(yRadio).c_str());
            newNode->append_attribute(ry);
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", color.c_str());
            newNode->append_attribute(fill);
        }

};

bool Ellipse::findMatchPosition(double pXValue, double pYValue){
    if((pXValue>=(Element::getXCoord()-Element::getSide()))&&(pXValue<=(Element::getXCoord()+Element::getSide()))&&
       (pYValue>=(Element::getYCoord()-yRadio))&&(pYValue<=(Element::getYCoord()+yRadio))){
        cout<<"\nDENTRO\n";
        return true;
       }
    else{
        cout<<"\nFUERA\n";
        return false;
    }
}

class Polyline:public Element{
    private:
        vector<vector<double>> xyCoords;
    public:
        Polyline(){Element::attribute = "polyline";};
        Polyline(vector<vector<double>> newXYCoords){xyCoords=newXYCoords;Element::attribute = "polyline";};
        void setXYCoord(vector<double> newxyCoords){xyCoords.push_back(newxyCoords);};
        vector<vector<double>> getXYCoord(){return xyCoords;};
        bool findMatchPosition(double pXValue, double pYValue);
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/
        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){
            
        }

};

bool Polyline::findMatchPosition(double pXValue, double pYValue){
    double maxYValue=xyCoords[0][1], maxXValue=xyCoords[0][0], minYValue=xyCoords[0][1], minXValue=xyCoords[0][0];

    for(int posicion=1;posicion<xyCoords.size();posicion++){
        if((xyCoords[posicion][1]>maxYValue)){
            maxYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][1]<minYValue)){
            minYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][0]>minXValue)){
            maxXValue=xyCoords[posicion][0];
        }
        if((xyCoords[posicion][0]<minXValue)){
            minXValue=xyCoords[posicion][0];
        }
    }
    if((pXValue>=minXValue)&&(pXValue<=maxXValue)&&(pYValue>=minYValue)&&(pYValue<=maxYValue)){
        cout<<"\ndentro\n";
        return true;
    }
    else{
        cout<<"\nafuera\n";
        return false;
    }

}

class Polygon:public Element{
    private:
        vector<vector<double>> xyCoords;
    public:
        Polygon(){Element::attribute = "polygon";};
        Polygon(vector<vector<double>> newCoords){xyCoords=newCoords;Element::attribute = "polygon";};
        void setXYCoord(vector<double> newxyCoords){xyCoords.push_back(newxyCoords);};
        vector<vector<double>> getXYCoord(){return xyCoords;};
        bool findMatchPosition(double pXValue, double pYValue);
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/
        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){
            
        }

};

bool Polygon::findMatchPosition(double pXValue, double pYValue){
    double maxYValue=xyCoords[0][1], maxXValue=xyCoords[0][0], minYValue=xyCoords[0][1], minXValue=xyCoords[0][0];

    for(int posicion=1;posicion<xyCoords.size();posicion++){
        if((xyCoords[posicion][1]>maxYValue)){
            maxYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][1]<minYValue)){
            minYValue=xyCoords[posicion][1];
        }
        if((xyCoords[posicion][0]>minXValue)){
            maxXValue=xyCoords[posicion][0];
        }
        if((xyCoords[posicion][0]<minXValue)){
            minXValue=xyCoords[posicion][0];
        }
    }
    if((pXValue>=minXValue)&&(pXValue<=maxXValue)&&(pYValue>=minYValue)&&(pYValue<=maxYValue)){
        cout<<"\ndentro\n";
        return true;
    }
    else{
        cout<<"\nafuera\n";
        return false;
    }

    cout<<minXValue<<" "<<minYValue<<" "<<maxXValue<<" "<<maxYValue<<" "<<pXValue<<" "<<pYValue<<endl;
}

class Line:public Element{
    private:
        double endXValue, endYValue;
    public:
        Line(){Element::attribute = "line";};
        Line(double newYCoord, double newXCoord, double newEndXValue,double newEndYValue){Element::coordX=newXCoord; Element::coordY=newYCoord;
        endXValue=newEndXValue;endYValue=newEndYValue; Element::attribute = "line";};
        void setEndXValue(double newEndXValue){endXValue=newEndXValue;};
        void setEndYValue(double newEndYValue){endYValue=newEndYValue;};
        double getEndXValue(){return endXValue;};
        double getEndYValue(){return endYValue;};
        bool findMatchPosition(double pXValue, double pYValue);
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/
        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){
            xml_node<> *newNode = myDoc->allocate_node(node_element, attribute.c_str());
            myDoc->first_node()->append_node(newNode);
            xml_attribute<> *x1 = myDoc->allocate_attribute("x1", to_string(coordX).c_str());
            newNode->append_attribute(x1);
            xml_attribute<> *y1 = myDoc->allocate_attribute("y1", to_string(coordY).c_str());
            newNode->append_attribute(y1);
            xml_attribute<> *x2 = myDoc->allocate_attribute("x2", to_string(endXValue).c_str());
            newNode->append_attribute(x2);
            xml_attribute<> *y2 = myDoc->allocate_attribute("y2", to_string(endYValue).c_str());
            newNode->append_attribute(y2);
            xml_attribute<> *fill = myDoc->allocate_attribute("fill", color.c_str());
            newNode->append_attribute(fill);
        }

};

bool Line::findMatchPosition(double pXValue, double pYValue){
    if((pXValue>=Element::getXCoord()&&pXValue<=endXValue)&&(pYValue>=Element::getYCoord()&&pYValue<=(endYValue-Element::getXCoord()))){
        cout<<"dentro";
        return true;
    }
    else{
        cout<<"afuera";
        return false;
    }
}
//falta

class Path:public Element{
    private:
        string d;
        vector<vector<double>>curvePositions;
    public:
        Path(){Element::attribute = "path";};
        Path(double newXMove, double newYMove, vector<vector<double>>newCurvePositions){Element::setXCoord(newXMove);Element::setXCoord(newYMove);
        curvePositions=newCurvePositions;Element::attribute = "path";};
        void setCurvePositions(vector<double> newCurvePosition){curvePositions.push_back(newCurvePosition);};
        void setD(string pNewD){Path::d = pNewD;};
        string getD(){return Path::d;}
        vector<vector<double>> getCurvePositions(){return curvePositions;};
        /*string getString(){return "Rectangle: X Value = "+to_string(Element::coordX)+" Y Value = "+to_string(Element::coordY)
        +" Horizontal Radio = "+to_string(xRadio)+" Vertical Radio = "+to_string(yRadio)+" Area = "+to_string(Element::getArea())+"\n";};*/
        void createSVGAttribute(xml_attribute<> *newAttr, xml_document<> *myDoc){
            
        }

};

class SVG{
    private:
        double height, width;
    public:
        SVG(){};
        void setHeight(double newHeight){height=newHeight;};
        void setWidth(double newWidth){width=newWidth;};
        double getHeight(){return height;};
        double getWidth(){return width;};
};
