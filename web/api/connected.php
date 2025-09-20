<?php 
    require_once '../include/db.php';

    if(isset($_POST)){
        header('Content-Type: application/json');

        function getSolde($number) {
            $db = getDBConnection();

            $query = "SELECT `solde` FROM user WHERE `number` = :username";
            $stmt = $db->prepare($query);
            $stmt->bindParam(':username', $number);
            $stmt->execute();

            $info = $stmt->fetch(PDO::FETCH_ASSOC);

            return $info["solde"];
        }

        function getLastTransactions($iban, $limit) {
            $db = getDBConnection();

            $query = "SELECT * FROM transactions WHERE `fromAcc` = :myIban OR `toAcc` = :Iban  ORDER BY date DESC LIMIT ".$limit;
            $stmt = $db->prepare($query);
            $stmt->bindParam(':myIban', $iban);
            $stmt->bindParam(':Iban', $iban);
            $stmt->execute();

            $info = $stmt->fetchAll(PDO::FETCH_ASSOC);

            return $info;
        }

        function addPayment($iban, $toiban, $price, $name) {
            $db = getDBConnection();

            $query = "INSERT INTO `transactions` (`fromAcc`, `toAcc`, `price`, `type`, `name`) VALUES (:facc, :toacc, :price, 'card', :name)";
            $stmt = $db->prepare($query);
            $stmt->bindParam(':facc', $iban);
            $stmt->bindParam(':toacc', $toiban);
            $stmt->bindParam(':price', $price);
            $stmt->bindParam(':name', $name);
            $stmt->execute();
        }

        function updateSolde($iban, $toiban, $price) {
            $db = getDBConnection();

            $query = "UPDATE `user` SET `solde` = `solde` - :price  WHERE `iban` = :myIban";
            $stmt = $db->prepare($query);
            $stmt->bindParam(':myIban', $iban);
            $stmt->bindParam(':price', $price);
            $stmt->execute();

            $query = "UPDATE `user` SET `solde` = `solde` + :price  WHERE `iban` = :toIban";
            $stmt = $db->prepare($query);
            $stmt->bindParam(':toIban', $toiban);
            $stmt->bindParam(':price', $price);
            $stmt->execute();
        }


        $cmd = isset($_POST['cmd']) ? $_POST['cmd'] : '';

        if($cmd == "getSold"){
            $solde = getSolde($_POST["number"]);

            $myObj = new stdClass();
            $myObj->solde = $solde;

            echo json_encode($myObj);
        }
        

        if ($cmd === "getLastTransactions") {
            $transactions = getLastTransactions($_POST["iban"], $_POST["limit"]);

            if (is_string($transactions)) {
                $transactions = json_decode($transactions, true);
            }

            $myArray = [];
            foreach ($transactions as $transaction) {
                $item = new stdClass();

                if($transaction["fromAcc"] === $_POST["iban"]){
                    $item->price = 0-$transaction["price"];
                }else{
                    $item->price = $transaction["price"];
                }

                $item->fromacc = $transaction["fromAcc"];
                $item->toacc   = $transaction["toAcc"];
                $item->motif   = $transaction["motif"];
                $item->type    = $transaction["type"];
                $item->name    = $transaction["name"];
                $item->date    = $transaction["date"];
                $myArray[] = $item;
            }

            echo json_encode($myArray);
        }
        
        if($cmd == "payment"){
            if($_POST["price"] <= getSolde($_POST["number"])){
                error_log("start");
                addPayment($_POST["iban"], $_POST["toiban"], $_POST["price"], $_POST["name"]);
                updateSolde($_POST["iban"], $_POST["toiban"], $_POST["price"]);
            }else{
                http_response_code(305);
            }
        }
    }