#include <QCoreApplication>

#include <iostream>
#include <memory>

using namespace std;

class IVoiture
{
public:
    virtual double prix() = 0;
};

class Aston_martin : public IVoiture
{
public:
    virtual double prix() override { return 999.99l; }
};

class Option_voiture : public IVoiture
{
public:
    Option_voiture(IVoiture *voiture, double prix_option)
    : voiture_(voiture)
    , prix_option_(prix_option)
    {}

    virtual double prix() override { return voiture_->prix() + prix_option_; }

protected:
    IVoiture *voiture_;
    double prix_option_;
};

class Option_clim : public Option_voiture
{
public:
    Option_clim(IVoiture *voiture) : Option_voiture(voiture, 1.0) {}
};

class Option_parachute : public Option_voiture
{
public:
    Option_parachute(IVoiture *voiture) : Option_voiture(voiture, 10.0) {}
};

class Option_amphibie : public Option_voiture
{
public:
    Option_amphibie(IVoiture *voiture) : Option_voiture(voiture, 100.0) {}
};

int main()
{
    IVoiture *voiture = new Aston_martin();   /// 999.99
    voiture = new Option_clim(voiture);       /// +1
    voiture = new Option_parachute(voiture);  /// +10
    voiture = new Option_amphibie(voiture);   /// +100
    std::cout << voiture->prix() << "\n";     /// = 1110.99
    return 0;
}
