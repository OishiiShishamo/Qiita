#include <algorithm>
#include <cmath>
#include <iostream>

// ただのRGBな色クラス
// 自由に持っていっていいよ
class Color {
public:
    double GetR() const { return r_; }
    double GetG() const { return g_; }
    double GetB() const { return b_; }
    void SetR(double r) { r_ = r; }
    void SetG(double g) { g_ = g; }
    void SetB(double b) { b_ = b; }
    void Saturate() {
        SetR(std::clamp(GetR(), static_cast<double>(0.0f), static_cast<double>(1.0f)));
        SetG(std::clamp(GetG(), static_cast<double>(0.0f), static_cast<double>(1.0f)));
        SetB(std::clamp(GetB(), static_cast<double>(0.0f), static_cast<double>(1.0f)));
    }
    void Saturate255() {
        SetR(std::clamp(GetR(), static_cast<double>(0.0f), static_cast<double>(255.0f)));
        SetG(std::clamp(GetG(), static_cast<double>(0.0f), static_cast<double>(255.0f)));
        SetB(std::clamp(GetB(), static_cast<double>(0.0f), static_cast<double>(255.0f)));
    }
    Color() = default;
    Color(double r, double g, double b) {
        r_ = r;
        g_ = g;
        b_ = b;
    }

    // 演算子オーバーロード
    Color operator+(const Color& rhs) const { return Color(GetR() + rhs.GetR(), GetG() + rhs.GetG(), GetB() + rhs.GetB()); }
    Color operator+(double scalar) const { return Color(GetR() + scalar, GetG() + scalar, GetB() + scalar); }
    Color operator-(const Color& rhs) const { return Color(GetR() - rhs.GetR(), GetG() - rhs.GetG(), GetB() - rhs.GetB()); }
    Color operator-(double scalar) const { return Color(GetR() - scalar, GetG() - scalar, GetB() - scalar); }
    Color operator*(const Color& rhs) const { return Color(GetR() * rhs.GetR(), GetG() * rhs.GetG(), GetB() * rhs.GetB()); }
    Color operator*(double scalar) const { return Color(GetR() * scalar, GetG() * scalar, GetB() * scalar); }
    Color operator/(const Color& rhs) const { return Color(GetR() / rhs.GetR(), GetG() / rhs.GetG(), GetB() / rhs.GetB()); }
    Color operator/(double scalar) const { return Color(GetR() / scalar, GetG() / scalar, GetB() / scalar); }
private:
    double r_ = 0;
    double g_ = 0;
    double b_ = 0;
};

/**
 * h : 0.0 ~ 360.0
 * s : 0.0 ~ 1.0
 * v : 0.0 ~ 1.0
 * 
 * return : 0 ~ 255の範囲で近似値を出す
 */
Color HsvToRgb(double h, double s = 1.0f, double v = 1.0f) {
    Color result;
    h = std::fmod(h, 360.0f);
    h /= 360.0f;
    result.SetR(std::abs(h * 6 - 3) - 1);
    result.SetG(2 - std::abs(h * 6 - 2));
    result.SetB(2 - std::abs(h * 6 - 4));
    result.Saturate();
    return (((result - 1) * s + 1) * v) * 255.0f;
}

// サンプルコード
int main() {
    double h = 0, s = 0, v = 0;
    std::cout << "Please input HSV" << std::endl;
    std::cin >> h >> s >> v;
    Color result = HsvToRgb(h, s, v);
    std::cout << result.GetR() << " " << result.GetG() << " " << result.GetB() << std::endl;
    return 0;
}