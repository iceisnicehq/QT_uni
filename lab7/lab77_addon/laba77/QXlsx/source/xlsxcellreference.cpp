// xlsxcellreference.cpp

#include "../header/xlsxcellreference.h"
#include "../header/xlsxworksheet_p.h"

#include <QMap>
#include <QRegularExpression>
#include <QStringList>

QT_BEGIN_NAMESPACE_XLSX

namespace {

int intPow(int x, int p)
{
    if (p == 0)
        return 1;
    if (p == 1)
        return x;

    int tmp = intPow(x, p / 2);
    if (p % 2 == 0)
        return tmp * tmp;
    else
        return x * tmp * tmp;
}

QString col_to_name(int col_num)
{
    QString col_str;
    int remainder;
    while (col_num) {
        remainder = col_num % 26;
        if (remainder == 0)
            remainder = 26;
        col_str.prepend(QChar('A' + remainder - 1));
        col_num = (col_num - 1) / 26;
    }
    return col_str;
}

int col_from_name(const QString &col_str)
{
    int col  = 0;
    int expn = 0;
    for (int i = col_str.size() - 1; i > -1; --i) {
        col += (col_str[i].unicode() - 'A' + 1) * intPow(26, expn);
        expn++;
    }

    return col;
}
} // namespace

/*!
    \class CellReference
    \brief For one single cell such as "A1"
    \inmodule QtXlsx

    The CellReference class stores the cell location in a worksheet.
*/

/*!
    Constructs an invalid Cell Reference
*/
CellReference::CellReference() = default;

/*!
    \overload
    Constructs the Reference form the given \a cell string.
*/
CellReference::CellReference(const QString &cell)
{
    init(cell);
}

/*!
    \overload
    Constructs the Reference form the given \a cell string.
*/
CellReference::CellReference(const char *cell)
{
    init(QString::fromLatin1(cell));
}

void CellReference::init(const QString &cell_str)
{
    static const QRegularExpression re(QStringLiteral("^\\$?([A-Z]{1,3})\\$?(\\d+)$"));
    QRegularExpressionMatch match = re.match(cell_str);
    if (match.hasMatch()) {
        const QString col_str = match.captured(1);
        const QString row_str = match.captured(2);
        _row                  = row_str.toInt();
        _column               = col_from_name(col_str);
    }
}

/*!
    Constructs a Reference by copying the given \a
    other Reference.
*/
CellReference::CellReference(const CellReference &other)
    : _row(other._row)
    , _column(other._column)
{
}

/*!
    Destroys the Reference.
*/
CellReference::~CellReference()
{
}

/*!
     Convert the Reference to string notation, such as "A1" or "$A$1".
     If current object is invalid, an empty string will be returned.
*/
QString CellReference::toString(bool row_abs, bool col_abs) const
{
    if (!isValid())
        return {};

    QString cell_str;
    if (col_abs)
        cell_str.append(QLatin1Char('$'));
    cell_str.append(col_to_name(_column));
    if (row_abs)
        cell_str.append(QLatin1Char('$'));
    cell_str.append(QString::number(_row));
    return cell_str;
}

/*!
 * Returns true if the Reference is valid.
 */
bool CellReference::isValid() const
{
    return _row > 0 && _column > 0;
}

QT_END_NAMESPACE_XLSX
