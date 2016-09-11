class ActivatorButton {

  public:
    ActivatorButton(int pin);
    void setup();
    bool isActivated();
    unsigned long getActivationTime();
};
