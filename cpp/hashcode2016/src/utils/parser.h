#ifndef PARSER_H
#define PARSER_H

#include <QStringList>
#include <QVector>

class Parser
{
public:
    static Parser parse(QString filename);

    inline bool is_valid() { return _valid; }

    QString get_line(int line_number);
    QVector<int> get_int_line(int line_number);

protected:
    Parser(QStringList lines = QStringList());

private:
    bool _valid;
    QStringList _lines;
};

#endif // PARSER_H
