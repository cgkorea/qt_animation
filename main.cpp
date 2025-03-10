#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>

class AnimatedItem : public QGraphicsPixmapItem {
public:
    AnimatedItem(const QPixmap &pixmap) : QGraphicsPixmapItem(pixmap), dx(5) {}

    void advance(int phase) override {
        if (!phase) return;
        setPos(x() + dx, y());
        if (x() > 400 || x() < 0) dx = -dx; // 화면 경계에서 방향 전환
    }

private:
    int dx;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QGraphicsScene scene(0, 0, 500, 500);
    QGraphicsView view(&scene);
    view.setRenderHint(QPainter::Antialiasing);

    QPixmap pixmap("object.png"); // 이동할 객체 이미지
    AnimatedItem *item = new AnimatedItem(pixmap);
    scene.addItem(item);
    item->setPos(0, 250);

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() { scene.advance(); });
    timer.start(50); // 50ms마다 프레임 갱신

    view.show();
    return app.exec();
}
