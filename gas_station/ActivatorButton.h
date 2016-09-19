class ActivatorButton {

  public:
    explicit ActivatorButton(int pin);
    void setup();
    bool isActivated();
    unsigned long getActivationTime();
};
