#include <QApplication>
#include <QWebEngineView>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QtMath>

int main(int argc, char *argv[])
{
    QJsonArray x,y,z, color;
    const auto nx = 180;
    const auto ny = 360;
    for (auto i=0; i<=nx; i++){
        QJsonArray xRow, yRow, zRow, colorRaw;
        auto theta = i*180.f/nx;
        for(auto j=0; j<=ny; j++) {
            auto phi = j*360.f/ny;
//            auto R = 1.f;
            auto R = qCos(qDegreesToRadians(theta));
            R = R*R*R*R*R*R;
            R = R >= 0 ? R : -R;
            auto r = R*qSin(qDegreesToRadians(theta));
            xRow.push_back(R * r * qCos(qDegreesToRadians(phi)));
            yRow.push_back(R * r * qSin(qDegreesToRadians(phi)));
            zRow.push_back(R * qCos(qDegreesToRadians(theta)));
            colorRaw.push_back(R);
        }
        x.push_back(xRow);
        y.push_back(yRow);
        z.push_back(zRow);
        color.push_back(colorRaw);
    }

    QJsonArray data;
    QJsonObject surface;

    surface["x"] = x;
    surface["y"] = y;
    surface["z"] = z;
    surface["surfacecolor"] = color;
    surface["type"] = "surface";
    surface["opacity"] = 0.5;
    surface["cmin"] = 0;
    surface["cmax"] = 1;

    data.push_back(surface);

    auto json = QJsonDocument(data);
//    auto txt = json.toJson(QJsonDocument::Compact);
    auto txt = json.toJson();
    QFile scriptTemplate("/home/sid/prog/plotly/html/generated.in.js");
    QFile script("/home/sid/prog/plotly/html/generated.js");
    if(scriptTemplate.open(QIODevice::ReadOnly) &&
        script.open(QIODevice::WriteOnly)
    ){
        script.write("var data = ");
        script.write(txt);
        script.write("\n\n");
        script.write(scriptTemplate.readAll());
        script.waitForBytesWritten(-1);
    }
    scriptTemplate.close();
    script.close();


    QApplication a(argc, argv);
    QWebEngineView *view = new QWebEngineView();
    view->load(QUrl::fromLocalFile("/home/sid/prog/plotly/html/generated.html"));
    view->show();
    return a.exec();
}
