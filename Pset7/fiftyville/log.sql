SELECT name
FROM people
WHERE id IN
(
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN
    (
        SELECT account_number
        FROM atm_transactions
        WHERE month = 7
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw'
    )
)
AND phone_number IN
(
    SELECT caller
    From phone_calls
    WHERE month = 7 AND day = 28 AND duration < 60 OR phone_number IN
    (
        SELECT receiver
        From phone_calls
        WHERE month = 7 AND day = 28 AND duration < 60
    )
)
AND passport_number IN
(
    SELECT passport_number
    FROM passengers
    WHERE flight_id = 36
)
AND license_plate IN
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE hour = 10 AND minute > 5 AND minute < 25 AND activity = 'exit'
);

-- The THIEF is: Bruce

SELECT city
FROM airports
WHERE id IN
(
    SELECT destination_airport_id
    FROM flights
    WHERE id = 36
);

-- The city the thief ESCAPED TO: New York City

SELECT name
FROM people
WHERE phone_number IN
(
    SELECT receiver
    FROM phone_calls
    WHERE caller IN
    (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND month = 7 AND day = 28 AND duration < 60
);

-- The ACCOMPLICE is: Robin
