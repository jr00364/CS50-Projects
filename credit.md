# Credit
**CS50 Introduction to Computer Science: Credit**

The task is to take a credit card number and to determine whether the card is an American Express, MasterCard, Visa or something else entirley

**American Express**: 15 digits, starts with 34 or 37

**MasterCard**: 16 digits, starts with 51,52,53,54 or 55

**Visa**: 13 or 16 digits, starts with 4


Additionally, every valid card number satisfies a **checksum** - a relationship between the set of digits that determine whether the card number is VALID or INVALID

**checksum:**

Multiply every other digit by 2, starting with the second-to-last digit
Add those products' digits together 
Add the sum to the sum of the digits that weren't multiplied by 2
If the totals last number is 0, number is VALID! 

So, in order for the credit card to be assigned to one of the companies above it must also satisfy the **checksum** argument

Card numbers used for testing https://developer.paypal.com/docs/classic/payflow/payflow-pro/payflow-pro-testing/#credit-card-numbers-for-testing
