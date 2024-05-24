namespace ui_elements {

    /********************************************************
     * The abstract class UiElement is parent of all other
     * classes in ui_elements. It ensures that all subclasses
     * implement the render method.
     ********************************************************/
    class UiElement {
    public:
        virtual ~UiElement() = default;

    private:
        virtual void render() const = 0; // abstract
    };

}