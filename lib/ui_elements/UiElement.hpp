
namespace ui_elements {

    class UiElement {
    public:
        virtual ~UiElement() = default;

    private:
        virtual void render() = 0; // abstract
    };

}