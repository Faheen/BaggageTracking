import java.awt.Frame;
import java.awt.Color;
import java.awt.Button;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

class Sample extends Frame{
    Label l1,l2,l3,l4;
    Button b1,b2,b3;
    Sample(){
        setLayout(null);
        
        
        l1=new Label("Welcome Karthi");
        l2=new Label("Welcome Sidhu");
        l3=new Label("Welcome Varsha");
        l4=new Label("Hello enter your name");
        
        b1=new Button("Karthik");
        b2=new Button("Sidhu");
        b3=new Button("Varsha");
        
        l1.setBounds(100, 300, 100, 25);
        l2.setBounds(100, 300, 100, 25);
        l3.setBounds(100, 300, 100, 25);
        l4.setBounds(100, 25, 150, 25);
        b1.setBounds(25, 100, 100, 25);
        b2.setBounds(150, 100, 100, 25);
        b3.setBounds(275, 100, 100, 25);
        
        
        b1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                remove(l3);
                remove(l2);
                add(l1);
            }
        });
        b2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                remove(l1);
                remove(l3);
                add(l2);
            }
        });
        b3.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                remove(l1);
                remove(l2);
                add(l3);
            }
        });
        
        
        add(b1);
        add(b2);
        add(b3);
        add(l4);
        
        setSize(600, 600);
        setBackground(Color.white);
        setVisible(true);
        
        
        
    }
    public static void main(String[] args) {
        new Sample();
    }
}