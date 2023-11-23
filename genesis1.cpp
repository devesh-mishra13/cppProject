#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <vector>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 30;
const int NUM_ENTITIES = 20;
const int MAX_ENERGY = 50;

class Entity {
public:
    int x, y;
    int energy;
    int color;

    Entity(int x, int y, int color) : x(x), y(y), energy(MAX_ENERGY), color(color) {}

    void moveTowardsCenter(const Entity& center) {
        int dx = center.x - x;
        int dy = center.y - y;

        // Move towards the center entity
        x += dx > 0 ? 1 : (dx < 0 ? -1 : 0);
        y += dy > 0 ? 1 : (dy < 0 ? -1 : 0);
    }

    void moveRandomly() {
        int newX = x + rand() % 3 - 1;
        int newY = y + rand() % 3 - 1;

        if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
            x = newX;
            y = newY;
        }
    }
};

int main(int argc, char *argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    QApplication app(argc, argv);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    view.setSceneRect(0, 0, GRID_SIZE * 10, GRID_SIZE * 10); // Adjust the size of the view

    std::vector<Entity> entities;
    for (int i = 0; i < NUM_ENTITIES; ++i) {
        entities.emplace_back(rand() % GRID_SIZE, rand() % GRID_SIZE, i % 2); // Alternate colors
    }

    for (int timeStep = 0; timeStep < 50; ++timeStep) {
        scene.clear();

        for (const Entity& entity : entities) {
            int x = entity.x * 10;
            int y = entity.y * 10;
            QGraphicsEllipseItem *circle = scene.addEllipse(x, y, 10, 10);
            if (entity.color == 0) {
                circle->setBrush(QBrush(Qt::blue));
            } else {
                circle->setBrush(QBrush(Qt::red));
            }
        }

        QTime dieTime = QTime::currentTime().addMSecs(100);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        view.show();

        app.processEvents();

        // Find center and move entities

        // Output information to the console (optional)

        // Perform any other necessary updates

        dieTime = QTime::currentTime().addMSecs(100);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    return app.exec();
}
