#include <QCoreApplication>

#include <iostream>
#include <memory>

using namespace std;

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

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
    Option_voiture(std::unique_ptr<IVoiture> voiture, double prix_option)
    : voiture_(std::move(voiture))
    , prix_option_(prix_option)
    {}

    virtual double prix() override { return voiture_->prix() + prix_option_; }

protected:
    std::unique_ptr<IVoiture> voiture_;
    double prix_option_;
};

class Option_clim : public Option_voiture
{
public:
    Option_clim(std::unique_ptr<IVoiture> voiture) : Option_voiture(std::move(voiture), 1.0) {}
};

class Option_parachute : public Option_voiture
{
public:
    Option_parachute(std::unique_ptr<IVoiture> voiture) : Option_voiture(std::move(voiture), 10.0) {}
};

class Option_amphibie : public Option_voiture
{
public:
    Option_amphibie(std::unique_ptr<IVoiture> voiture) : Option_voiture(std::move(voiture), 100.0) {}
};

int main()
{
    auto voiture = std::unique_ptr<IVoiture>(make_unique<Aston_martin>()); /// 999.99
    voiture = make_unique<Option_clim>(std::move(voiture));                /// +1
    voiture = make_unique<Option_parachute>(std::move(voiture));           /// +10
    voiture = make_unique<Option_amphibie>(std::move(voiture));            /// +100
    std::cout << voiture->prix() << "\n";                                  /// = 1110.99
    return 0;
}
