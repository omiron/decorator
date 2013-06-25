#include <iostream>
#include <typeinfo>
#include <assert.h>

using namespace std;

class Window 
{
    public:
    virtual void draw() = 0;
};

class NormalWindow: public Window 
{
    int width, height;
    public:
    NormalWindow(int w, int h)
    {
        width = w;
        height = h;
    }
 
    void draw()
    {
        cout << "\tNormalWindow: " << width << ", " << height << endl;
    }
};

class CircleWindow: public Window 
{
    int radius;
    public:
    CircleWindow(int r)
    {
        radius = r;
    }
 
    void draw()
    {
        cout << "\tCircleWindow: " << radius << endl;
    }
};

class Decorator: public Window
{
    Window *window;
    public:
    Decorator(Window *w)
    {
        window = w;
    }
 
    Decorator()
    {
        window = NULL;
    }

    void draw(){
        if (window)
            window->draw();
    }

    void add(Window *dc) {
        if (!window)
        {
            window = dc;
            return;
        }

        //TODO: assert(type(window) == Decorator)   
        ((Decorator *)window)->add(dc);

    }

};

class BorderDecorator: public Decorator
{
  public:
    BorderDecorator(Window *w): Decorator(w){}
    BorderDecorator(): Decorator(){}
 
    void draw()
    {
        Decorator::draw();
        cout << "\tBorderDecorator: " << endl;
    }

};

class ScrollDecorator: public Decorator
{
  public:
    ScrollDecorator(Window *w): Decorator(w){}
    ScrollDecorator(): Decorator(){}
 
    void draw()
    {
        Decorator::draw();
        cout << "\tScrollDecorator: " << endl;
    }
};

int main()
{
    cout << "Compose on construct" << endl;
    Window *aWidget = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new NormalWindow(100, 100))));
    aWidget->draw();

    cout << "Compose on construct in the same manner" << endl;
    
    Window *aWidget_ = new BorderDecorator(new CircleWindow(100));
    aWidget_->draw();

    cout << "Adding to live_instance" << endl;
    Decorator *live_instance = new BorderDecorator();
    cout << "\tNow is only simple BorderDecorator" << endl;
    live_instance->draw();
    live_instance->add(new ScrollDecorator());
    cout << "\tNow has ScrollDecorator" << endl;
    live_instance->draw();

    live_instance->add(new CircleWindow(10));
    cout << "\tNow has CircleWindow" << endl;
    live_instance->draw();
}
