class Animal
{
private:
    string name;
public:
    Animal();
    Animal(string n);
    int setWeight(int weight);
    bool surviveArea(Animal& a) const;
    bool food(Animal& a) const;
    bool omnivore(Animal& a) const;
    bool amphibiou(Animal& a) const;
}

