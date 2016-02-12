#ifndef PARSER_H
#define PARSER_H

#include <QStringList>
#include <QVector>

class Parser
{
public:
    static Parser parse(QString filename);

    QString get_line(int line_number);
    QVector<int> get_int_line(int line_number);

protected:
    Parser(QStringList lines);

private:
    QStringList _lines;
};

#endif // PARSER_H
