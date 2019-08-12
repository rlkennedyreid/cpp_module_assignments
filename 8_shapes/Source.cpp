#include<vector>

#include "square.h"
#include "circle.h"
#include "cube.h"
#include "sphere.h"
#include "prism.h"

using std::cout;
using std::endl;
using std::vector;
int main(){
    
    const double a{ 1.5 }, b{ 1.5 }, c{ 1.5 };
    vector<Shape*> shape_vector;
    shape_vector.push_back(new Rectangle(a, b));
    shape_vector.push_back(new Square(a));
    shape_vector.push_back(new Ellipse(a, b));
    shape_vector.push_back(new Circle(a));
    shape_vector.push_back(new Cuboid(a, b, c));
    shape_vector.push_back(new Cube(a));
    shape_vector.push_back(new Ellipsoid(a, b, c));
    shape_vector.push_back(new Sphere(a));
    shape_vector.push_back(new Prism(a, shape_vector[0]));

    for (auto vector_iterator = shape_vector.begin();
        vector_iterator < shape_vector.end();
        vector_iterator++){
        cout << "For " << (*vector_iterator)->PrintType() <<
            " Area is " << (*vector_iterator)->GetArea() <<
            endl << "Volume is " << (*vector_iterator)->GetVolume() << endl << endl;
    }
    return 0;
}