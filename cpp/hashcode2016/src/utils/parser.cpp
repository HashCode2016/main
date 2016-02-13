#include "parser.h"

#include "macro.h"

#include <QFile>

#define EOL '\n'
#define SEP ' '

Parser::Parser(QStringList lines) :
    _valid(false),
    _lines(lines)
{
    if(_lines.count() > 0)
    {   _valid = true;
    }
}

Parser Parser::parse(QString filename)
{
    if(QFile::exists(filename))
    {   QFile f(filename);
        if(f.open(QIODevice::ReadOnly))
        {   return Parser(QString(f.readAll()).split(EOL));
        }
        else
        {   ERROR("Parser","parse","can't open file in readonly mode !");
        }
    }
    else
    {   ERROR("Parser","parse","file is missing !");
    }
    return Parser();
}

QString Parser::get_line(int line_number)
{
    QString line;
    if(line_number < _lines.count())
    {   line = _lines[line_number];
    }
    else
    {   ERROR("Parser","get_line","line index out of bounds !");
    }
    return line;
}

QVector<int> Parser::get_int_line(int line_number)
{
    QVector<int> v;
    if(line_number < _lines.size())
    {   QStringList elems = _lines[line_number].split(SEP);
        v = QVector<int>(elems.count(), 0);
        bool ok(true);
        for(int i = 0; i < elems.count(); ++i)
        {   v[i] = elems[i].toInt(&ok);
            if(!ok)
            {   ERROR("Parser","get_int_line","convertion failed !");
            }
        }
    }
    else
    {   ERROR("Parser","get_int_line","line index out of bounds !");
    }
    return v;
}



