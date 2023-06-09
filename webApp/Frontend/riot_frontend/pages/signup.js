import { useState } from "react";
import { useRouter } from "next/router";
import styles from '/styles/signup.module.css'

export default function SignUp() {
    const router = useRouter();
    const [firstname, setFirstname] = useState('');
    const [lastname, setLastname] = useState('');
    const [email, setEmail] = useState('');
    const [password, setPassword] = useState('');
    const [errors, setErrors] = useState({});

    const checkForm = () => {
        let errors = {};
        let isValid = true;

        if (!firstname) {
            errors.firstname = 'First name is required';
            isValid = false;
        }

        if (!lastname) {
            errors.lastname = 'Last name is required';
            isValid = false;
        }

        if (!email) {
            errors.email = 'Email is required';
            isValid = false;
        } else if (!/\S+@\S+\.\S+/.test(email)) {
            errors.email = 'Email is not valid';
            isValid = false;
        }

        if (!password) {
            errors.password = 'Password is required';
            isValid = false;
        } else if (password.length < 6) {
            errors.password = 'Password must be at least 6 characters';
            isValid = false;
        }

        setErrors(errors);
        return isValid;
    }

    const handleSubmit = (event) => {
        event.preventDefault();
        if (checkForm()) {
            console.log({ firstname, lastname, email, password });
        }
    };

    return (
        <div className="signup">
            <nav>
                <ul>
                    <li><a href="/">Home</a></li>
                    <li><a href="/signin">Log In</a></li>
                    <li><a href="/contact">Contact</a></li>
                </ul>
            </nav>
            <h1 className="signup-header">Sign Up</h1>
            <div className="signup-body">
                <form onSubmit={handleSubmit}>
                <div className={styles['form-group']}>
                        <label className={styles.label}>
                            First name:
                            <input
                                type="text"
                                value={firstname}
                                onChange={(e) => setFirstname(e.target.value)}
                            /> 
                            {errors.firstname && <span className={styles.error}>{errors.firstname}</span>}
                        </label>
                    </div>
                    <div className={styles['form-group']}>
                        <label className={styles.label}>
                            Last name:
                            <input
                                type="text"
                                value={lastname}
                                onChange={(e) => setLastname(e.target.value)}
                            /> 
                            {errors.lastname && <span className={styles.error}>{errors.lastname}</span>}
                        </label>
                    </div>
                    <div className={styles['form-group']}>
                        <label className={styles.label}>
                            Email:
                            <input
                                type="email"
                                value={email}
                                onChange={(e) => setEmail(e.target.value)}
                            /> 
                            {errors.email && <span className={styles.error}>{errors.email}</span>}
                        </label>
                    </div>
                    <div className={styles['form-group']}>
                        <label className={styles.label}>
                            Password:
                            <input
                                type="password"
                                value={password}
                                onChange={(e) => setPassword(e.target.value)}
                            />
                            {errors.password && <span className={styles.error}>{errors.password}</span>}
                        </label>
                    </div>
                    <button type="submit">Sign up</button>
                    <button>Cancel</button>
                    <footer>
                        <p>If you already have an account, please <a href="/signin">log in here</a>.</p>
                    </footer>
                </form>
            </div>
        </div>
    );
}
