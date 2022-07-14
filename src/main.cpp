#include <iostream> 

int main() {

    const int image_width = 500;
    const int image_height = 500;

    std::cout << "Hallo" << image_width << ' ' << image_height << "kp";

    for (int i = image_height - 1; i >= 0; --i) {
        for (int j = 0; i < image_width; ++i) {
            auto r = double(j) / (image_width - 1);
            auto g = double(i) / (image_height - 1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';

        }
    }
}