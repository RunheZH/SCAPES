#include "../inc/highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::darkYellow);
//    keywordFormat.setFontWeight(QFont::Bold);
    const QString keywordPatterns[] = {
        QStringLiteral("\\bdci\\b"),
        QStringLiteral("\\bdca\\b"),
        QStringLiteral("\\brdi\\b"),
        QStringLiteral("\\bprt\\b"),
        QStringLiteral("\\bmov\\b"),
        QStringLiteral("\\badd\\b"),
        QStringLiteral("\\bcmp\\b"),
        QStringLiteral("\\bjls\\b"),
        QStringLiteral("\\bjmr\\b"),
        QStringLiteral("\\bjep\\b"),
        QStringLiteral("\\bjmp\\b"),
        QStringLiteral("\\bend\\b"),
    };
    for (const QString &pattern : keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    labelFormat.setFontWeight(QFont::Bold);
    labelFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("(\\b[a-zA-Z0-9]+\\b)(:)"));
    rule.format = labelFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(QColor(96,163,78));
    rule.pattern = QRegularExpression(QStringLiteral("#[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
