#include "parser.h"

#include "macro.h"

#include <QFile>

#define EOL '\n'
#define SEP ' '

Parser::Parser(QStringList lines) :
    _lines(lines)
{
}

Parser Parser::parse(QString filename)
{
    if(QFile::exists(filename))
    {   QFile f(filename);
        if(f.open(QIODevice::ReadOnly))
        {   return Parser(QString(f.readAll()).split(EOL));
        }
        else
        {   ERROR("Parser: Can't open file in readonly mode !");
        }
    }
    else
    {   ERROR("Parser: File is missing !");
    }
}

QString Parser::get_line(int line_number)
{
    if(line_number < _lines.count())
    {   return _lines[line_number];
    }
    else
    {   ERROR("Parser: Line index out of bounds !");
    }
}

QVector<int> Parser::get_int_line(int line_number)
{
    if(line_number < _lines.size())
    {   QStringList elems = _lines[line_number].split(SEP);
        QVector<int> v(elems.count(), 0);
        bool ok(true);
        for(int i = 0; i < elems.count(); ++i)
        {   v[i] = elems[i].toInt(&ok);
            if(!ok)
            {   ERROR("Parser: Convertion failed !");
            }
        }
        return v;
    }
    else
    {   ERROR("Parser: Line index out of bounds !");
    }
}



