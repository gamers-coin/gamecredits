// Original Code: Copyright (c) 2011-2014 The Bitcoin Core Developers
// Modified Code: Copyright (c) 2015 Gamecredits Foundation
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GAMECREDITSADDRESSVALIDATOR_H
#define GAMECREDITSADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class GamecreditsAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GamecreditsAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Gamecredits address widget validator, checks for a valid gamecredits address.
 */
class GamecreditsAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit GamecreditsAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // GAMECREDITSADDRESSVALIDATOR_H
