#include <iostream>
#include <cmath>

class Triad {
protected:
    int a, b, c;
public:
    Triad(int a_, int b_, int c_) : a(a_), b(b_), c(c_) {}

    void setNumbers(int a_, int b_, int c_) {
        a = a_;
        b = b_;
        c = c_;
    }

    int getSum() const {
        return a + b + c;
    }
};

class Triangle : public Triad {
public:
    Triangle(int a_, int b_, int c_) : Triad(a_, b_, c_) {}

    double calculateAngle(int side1, int side2, int side3) const {
        return acos((pow(side1, 2) + pow(side2, 2) - pow(side3, 2)) / (2 * side1 * side2)) * 180.0 / 3.14;
    }

    double calculateArea() const {
        double s = getSum() / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    void printAngles() const {
        double angleA = calculateAngle(b, c, a);
        double angleB = calculateAngle(c, a, b);
        double angleC = 180.0 - angleA - angleB;
        std::cout << "Angles of the triangle: " << angleA << ", " << angleB << ", " << angleC << std::endl;
    }
};

int main() {
    Triangle triangle(3, 4, 5);

    std::cout << "Sum of triangle sides: " << triangle.getSum() << std::endl;
    std::cout << "Area of the triangle: " << triangle.calculateArea() << std::endl;
    triangle.printAngles();

    return 0;
}


#include <iostream>
#include <functional>

class Title {
    std::string text;
public:
    Title(const std::string& text_) : text(text_) {}
    void setText(const std::string& text_) { text = text_; }
    std::string getText() const { return text; }
    void display() const { std::cout << "Title: " << text << std::endl; }
};

class Button {
    std::string label;
    std::function<void()> callback;
public:
    Button(const std::string& label_) : label(label_) {}
    void setLabel(const std::string& label_) { label = label_; }
    std::string getLabel() const { return label; }
    void setCallback(std::function<void()> callback_) { callback = callback_; }
    void press() const { if (callback) callback(); }
    void display() const { std::cout << "Button: " << label << std::endl; }
};

class Window {
    Title title;
    Button button;
public:
    Window(const std::string& titleText, const std::string& buttonText)
        : title(titleText), button(buttonText) {
        button.setCallback([this]() { this->onButtonPress(); });
    }

    void onButtonPress() const {
        std::cout << "Button was pressed! Performing callback function." << std::endl;
    }

    void setTitleText(const std::string& text) { title.setText(text); }
    std::string getTitleText() const { return title.getText(); }

    void setButtonText(const std::string& text) { button.setLabel(text); }
    std::string getButtonText() const { return button.getLabel(); }

    void display() const {
        title.display();
        button.display();
    }

    void pressButton() const {
        button.press();
    }
};

int main() {
    Window window("Main Window", "Click Me");

    window.display();

    window.pressButton();

    return 0;
}

#include <iostream>
#include <algorithm>
#include <cstring>

class String {
protected:
    char* str;
    size_t length;

public:
    String() : str(nullptr), length(0) {}

    String(const char* s) {
        length = strlen(s);
        str = new char[length + 1];
        std::copy(s, s + length + 1, str);
    }

    String(const String& other) {
        length = other.length;
        str = new char[length + 1];
        std::copy(other.str, other.str + length + 1, str);
    }

    String& operator=(const String& other) {
        if (this == &other)
            return *this;

        delete[] str;

        length = other.length;
        str = new char[length + 1];
        std::copy(other.str, other.str + length + 1, str);

        return *this;
    }

    virtual ~String() {
        delete[] str;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& s) {
        os << s.str;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, String& s) {
        char buffer[1000];
        is >> buffer;
        s = String(buffer);
        return is;
    }
};

class UpperCaseString : public String {
public:
    using String::String;

    UpperCaseString(const UpperCaseString& other) : String(other) {}

    UpperCaseString& operator=(const UpperCaseString& other) {
        if (this == &other)
            return *this;

        String::operator=(other);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const UpperCaseString& s) {
        for (size_t i = 0; i < s.length; ++i) {
            os << static_cast<char>(toupper(s.str[i]));
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, UpperCaseString& s) {
        char buffer[1000];
        is >> buffer;
        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            buffer[i] = toupper(buffer[i]);
        }
        s = UpperCaseString(buffer);
        return is;
    }
};

int main() {
    String s1("Hello");
    UpperCaseString s2("world");

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    std::cout << "Enter a new string for s1: ";
    std::cin >> s1;
    std::cout << "New s1: " << s1 << std::endl;

    std::cout << "Enter a new uppercase string for s2: ";
    std::cin >> s2;
    std::cout << "New s2: " << s2 << std::endl;

    return 0;
}

