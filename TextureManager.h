#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;


class TextureManager {
private:
    // For variables
    Texture* textures;
    string* names;
    int capacity;
    int idx;
    Texture dummyTexture;

private:
    // For functions
    int getIndexFromName(string n) {
        for (int i = 0; i < idx; i++) {
            if (names[i] == n) return i;
        }
        return -1;
    }

    void resize(int resizeBy) {
        Texture* temp = new Texture[capacity + resizeBy];
        string* tempS = new string[capacity + resizeBy];
        for (int i = 0; i < this->capacity; i++) {
            temp[i] = this->textures[i];
            tempS[i] = this->names[i];
        }
        delete[] this->textures, delete[] this->names;
        this->textures = temp;
        this->names = tempS;
    }

public:
    TextureManager(int t = 10) : capacity(t), idx(0) {
        textures = new Texture[capacity];
        names = new string[capacity];
    };

    void addTexture(string source, string n) {
        cout << "Added texture " << n << endl;
        if (idx >= capacity) resize(2);
        Texture temp;
        if (!temp.loadFromFile(source)) {
            cout << "Couldn't load " << n << " texture from " << source << endl;
        }
        textures[idx] = temp;
        names[idx] = n;
        idx++;
    }

    Texture& getTexture(int n) {
        if (n < idx)
            return textures[n];
        return dummyTexture;
    }

    Texture& getTexture(string name) {
        int index = getIndexFromName(name);
        cout << "Index of " << name << " texture is " << index << endl;
        if (index != -1)
            return textures[index];
        return dummyTexture;
    }

    ~TextureManager() {
        delete textures;
        textures = nullptr;
    }
};