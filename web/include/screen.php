<?php 

    require_once 'include/db.php';

    function getSolde($number) {
        $db = getDBConnection();

        $query = "SELECT `solde` FROM user WHERE `number` = :username";
        $stmt = $db->prepare($query);
        $stmt->bindParam(':username', $number);
        $stmt->execute();

        $info = $stmt->fetch(PDO::FETCH_ASSOC);

        return $info["solde"];
    }

    function getIBAN($number) {
        $db = getDBConnection();

        $query = "SELECT `iban` FROM user WHERE `number` = :username";
        $stmt = $db->prepare($query);
        $stmt->bindParam(':username', $number);
        $stmt->execute();

        $info = $stmt->fetch(PDO::FETCH_ASSOC);

        return $info["iban"];
    }

    function lastTransactions($iban) {
        $db = getDBConnection();

        $query = "SELECT * FROM transactions WHERE `fromAcc` = :myIban OR `toAcc` = :iban ORDER BY date DESC;";
        $stmt = $db->prepare($query);
        $stmt->bindParam(':myIban', $iban);
        $stmt->bindParam(':iban', $iban);
        $stmt->execute();

        $info = $stmt->fetchAll(PDO::FETCH_ASSOC);
        $i = 0;

        foreach($info as $row){
            if($row["type"] == "transfert"){
                if($iban === $row["fromAcc"]){
                    echo "{id:" . $i . ", who:'". $row["toAcc"] . "', date: '" . $row["date"] . "', amount: -".$row["price"]. "},";
                }elseif($iban === $row["toAcc"]){
                    echo "{id:" . $i . ", who:'". $row["fromAcc"] . "', date: '" . $row["date"] . "', amount: +".$row["price"]. "},";
                }
            }
            
            $i++;
        }
    }

?>