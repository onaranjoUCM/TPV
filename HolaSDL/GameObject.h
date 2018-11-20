#ifndef GameObjectH
#define GameObjectH

class GameObject {
private:
	
public:
	~GameObject() { }
	virtual void render() = 0;
	virtual void update() = 0;
	virtual void handleEvents() = 0;
};

#endif